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

float image_average(image_t * img)
{
	float sum = 0;
	int cnt = 0;

	float *ip;
    float *endp;

    ip = img->data;
    endp = &ip[3 * img->width * img->height];

    while (ip < endp) {
        sum += *ip;
        cnt ++;
        ip ++;
    }

	return (float)(sum / (float)cnt);
}
