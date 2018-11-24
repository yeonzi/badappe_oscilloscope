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
#include <stdlib.h>

#include <dirent.h>

#include <utils.h>

int create_tmp_dir(void)
{
	fprintf(stderr, "Creating Temp Dir.\n");
	/* Windows command lines are different from others */

#if defined(WIN32) || defined(WIN64) || defined(WINNT)

	/* Add Windows command lines here */

#else /* ! WIN32 || WIN64 || WINNT */

	system("mkdir -p ./tmp");
	system("mkdir -p ./tmp/frames");
	system("mkdir -p ./tmp/frames_proc");

#endif /* WIN32 || WIN64 || WINNT */

	return 0;
}

int remove_tmp_dir(void)
{
	/* Windows command lines are different from others */

#if defined(WIN32) || defined(WIN64) || defined(WINNT)

	/* Add Windows command lines here */

#else /* ! WIN32 || WIN64 || WINNT */

	system("rm -rf ./tmp");

#endif /* WIN32 || WIN64 || WINNT */

	return 0;
}

int transform_video(const char * input_path)
{
	char commands[255];

	fprintf(stderr, "Extracting Frames.\n");

	sprintf(commands, "ffmpeg -loglevel 0 -stats -i %s -vf fps=24 ./tmp/frames/v-%%05d.bmp", input_path);

	system(commands);

	fprintf(stderr, "Extracting Audio Track.\n");

	sprintf(commands, "ffmpeg -loglevel 0 -stats -i %s -vn -ar 44100 -ac 2 -ab 192k -f adts ./tmp/Sample.aac", input_path);

	system(commands);

	return 0;
}

int get_frame_cnt(void)
{
	int frame_count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir("./tmp/frames");
	while ((entry = readdir(dirp)) != NULL) {
	    if (entry->d_type == DT_REG) {
	         frame_count++;
	    }
	}
	closedir(dirp);

	return frame_count;
}
