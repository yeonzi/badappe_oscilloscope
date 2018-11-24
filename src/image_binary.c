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

#include <image.h>
#include <image_binary.h>
#include <image_gray.h>
#include <image_average.h>

int image_binary(image_t * img)
{
	float average;

	float *ip;
    float *endp;

	image_gray(img);

	average = image_average(img) / 2.0;

	ip = img->data;
    endp = &ip[3 * img->width * img->height];

    while (ip < endp) {
        if (*ip > average && *ip > 1) {
        	*ip = 255;
        } else {
        	*ip = 0;
        }
        ip ++;
    }

	return 0;
}
