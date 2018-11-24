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

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <image.h>
#include <image_binary.h>
#include <image_edge_dect.h>
#include <bmp.h>
#include <utils.h>
#include <wave.h>
#include <path.h>

int frame_cnt = 0;
int frame_index = 0;
int frame_w = 0;
int frame_h = 0;
int frame_s = 0;

void show_proc(int signal);

int main(void)
{
	extern int frame_cnt;
	extern int frame_index;
	extern int frame_w;
	extern int frame_h;
	extern int frame_s;
	char path[64];
	image_t * img;
	wave_t * wav;
	struct sigaction sa;


	create_tmp_dir();

	transform_video("./input.mp4");

	frame_cnt = get_frame_cnt();

	fprintf(stderr, "Do Processing Workflow On Each Frame.\n");

	sa.sa_handler = &show_proc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &sa, NULL);
	alarm(3);

	wav = wave_new(2, 48000, (48000 / 24) * frame_cnt);

	for (frame_index = 1; frame_index <= frame_cnt; frame_index++) {
		
		sprintf(path, "./tmp/frames/v-%05d.bmp", frame_index);

		img = bmp_read(path);

		if (frame_w == 0) {
			frame_w = img->width;
			frame_h = img->height;
			frame_s = 3 * frame_w * frame_h * 4;
		}

		image_binary(img);

		image_edge_dect(img);

		image_binary(img);

		// sprintf(path, "./tmp/frames_proc/v-%05d.bmp", frame_index);

		// bmp_save(img, path);

		gen_path(img, wav, frame_index - 1);

		image_free(img);
		
	}

	raise(SIGALRM);

	fprintf(stderr, "\nProcess end.\n");

	alarm(0);

	fprintf(stderr, "\nSaving.\n");

	wave_save(wav, "./out.wav");

	wave_free(wav);

	fprintf(stderr, "\nCleaning.\n");

	remove_tmp_dir();

	return 0;
}

void show_proc(int signal)
{
	extern int frame_cnt;
	extern int frame_index;
	extern int frame_s;

	static int priv_index = 0;
	static int time_s = 0;
	static int time_m = 0;
	static int time_h = 0;

	float fps;
	float kbps;
	float speed;

	fps = (frame_index - priv_index) / 3.0;
	kbps = (fps * frame_s)/1000.0;
	priv_index = frame_index;
	speed = (float)fps / (float)24;
	time_s += 3;

	if (time_s == 60) {
		time_s = 0;
		time_m ++;
	}

	if (time_m == 60) {
		time_m = 0;
		time_h ++;
	}

	fprintf(stderr, "\rframe= %d fps= %.1f time=%02d:%02d:%02ds bitrate=%.1fkbits/s speed=%.2fx SIG=%d",\
		frame_index, fps, time_h, time_m, time_s, kbps, speed, signal);
	fflush(stderr);

	alarm(3);
}
