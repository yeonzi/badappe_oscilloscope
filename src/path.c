/********************************************************************************
The MIT License
Copyright (c) 2018 Yeonji
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
********************************************************************************/

#include <path.h>

int gen_path(image_t * img, wave_t * wav, int frame_no)
{
	static int * origin_x_pos = NULL;
	static int * origin_y_pos = NULL;
	static int * origin_dist  = NULL;
	static int * origin_avail = NULL;
	static int * sorted_x = NULL;
	static int * sorted_y = NULL;

	int graph_size = 0;
	int point_cnt;

	int wav_length = (48000 / 24);

	static int last_x = 0;
	static int last_y = 0;

	return 0;
}
