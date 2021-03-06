/******************************************************************************
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004
 
Copyright (C) 2017-2018 Yeonji <yeonji@ieee.org>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.
 
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 
 0. You just DO WHAT THE FUCK YOU WANT TO.
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <wave.h>

wave_t * wave_new(int channel, int rate, int length)
{
	int ch_index;
	wave_t * wave;

	wave = malloc(sizeof(wave_t));

	if (wave == NULL) {
		return NULL;
	}

	wave->data = malloc(channel * sizeof(int16_t *));

	if (wave->data == NULL) {
		free(wave);
		return NULL;
	}

	for (ch_index = 0; ch_index < channel; ch_index++) {
		wave->data[ch_index] = malloc(length * sizeof(int16_t));

		if (wave->data[ch_index] == NULL) {
			while (ch_index >= 0) {
				free(wave->data[ch_index]);
				ch_index --;
			}
			free(wave);
			return NULL;
		}
	}

	wave->channel = channel;
	wave->rate = rate;
	wave->length = length;

	return wave;
}

int wave_free(wave_t * wave)
{
	int ch_index;
	for (ch_index = 0; ch_index < wave->channel; ch_index++) {
		free(wave->data[ch_index]);
	}
	free(wave);
	return 0;
}

#define RIFF_CHUNKID 0x46464952 /* RIFF in ascii */
#define RIFF_FORMAT  0x45564157 /* WAVE in ascii */

typedef struct {
	uint32_t ChunkID;     /* should always be RIFF_CHUNKID */
	uint32_t ChunkSize;
	uint32_t Format;      /* should always be RIFF_FORMAT */
} riff_header_t;

#define RIFF_SCHUNK_FMT  0x20746d66 /* "fmt " in ascii */
#define RIFF_SCHUNK_DATA 0x61746164 /* "data" in ascii */

typedef struct {
	uint32_t Subchunk1ID;   /* should always be RIFF_SCHUNK_FMT */
	uint32_t Subchunk1Size; /* 16 */
	uint16_t AudioFormat;   /* 1 for PCM */
	uint16_t NumChannels;   /* Mono = 1, Stereo = 2, etc. */
	uint32_t SampleRate;    /* 8000, 44100, etc. */
	uint32_t ByteRate;      /* == SampleRate * NumChannels * BitsPerSample/8 */
	uint16_t BlockAlign;    /* == NumChannels * BitsPerSample/8 */
	uint16_t BitsPerSample; /* 8 bits = 8, 16 bits = 16, etc. */
}__attribute__((packed)) riff_fmt_chunk_t;

typedef struct {
	uint32_t Subchunk2ID;   /* shoule always be RIFF_SCHUNK_DATA */
	uint32_t Subchunk2Size; /* == NumSamples * NumChannels * BitsPerSample/8 */
} riff_data_chunk_t;

int wave_save(wave_t * wave, const char * path)
{
	riff_header_t header;
	riff_fmt_chunk_t fmt;
	riff_data_chunk_t data;

	int ch_index;
	int frame_index;

	FILE * fp;

	fp = fopen(path, "wb");
	if (fp == NULL) {
		perror("Cannot open wav file");
		return -1;
	}

	header.ChunkID   = RIFF_CHUNKID;
	header.ChunkSize = 36 + wave->length * wave->channel * 2;
	header.Format    = RIFF_FORMAT;

	fwrite(&header, sizeof(riff_header_t), 1, fp);

	fmt.Subchunk1ID   = RIFF_SCHUNK_FMT;
	fmt.Subchunk1Size = 16;
	fmt.AudioFormat   = 1;
	fmt.NumChannels   = wave->channel;
	fmt.SampleRate    = wave->rate;
	fmt.BlockAlign    = 4;
	fmt.BitsPerSample = 16;

	fmt.ByteRate      = fmt.SampleRate * (fmt.BitsPerSample / 8);

	fwrite(&fmt, sizeof(riff_fmt_chunk_t), 1, fp);

	data.Subchunk2ID   = RIFF_SCHUNK_DATA;
	data.Subchunk2Size = wave->channel * wave->length * (fmt.BitsPerSample / 8);

	fwrite(&data, sizeof(riff_data_chunk_t), 1, fp);

	for (frame_index = 0; frame_index < wave->length; frame_index++) {
		for (ch_index = 0; ch_index < wave->channel; ch_index++) {
			fwrite(&wave->data[ch_index][frame_index], sizeof(int16_t), 1, fp);
		}
	}

	fclose(fp);
	return 0;
}

#if 0

/* test program */

#include <math.h>

int __attribute__((weak)) main(int argc, char const *argv[])
{
	wave_t * test;
	int frame;
	float fact;
	char cnt = 0;

	test = wave_new(2,48000,480000);

	for (frame = 0; frame < 480000; frame++) {
		cnt ++;
		if (cnt > 0) {
			fact = 30000.0;
		} else {
			fact = 25000.0;
		}
		test->data[0][frame] = (int16_t)(cos(frame * (3.14 / 24.0)) * fact);
		test->data[1][frame] = (int16_t)(sin(frame * (3.14 / 24.0)) * fact);
	}
	
	wave_save(test, "./test.wav");

	wave_free(test);
	return 0;
}

#endif
