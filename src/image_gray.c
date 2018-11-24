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
#include <image_gray.h>

int image_gray(image_t * img)
{
	float R;
	float G;
	float B;
	float Y;

	float *ip;
    float *endp;

    ip = img->data;
    endp = &ip[3 * img->width * img->height];

    while (ip < endp) {
        B = ip[0];
        G = ip[1];
        R = ip[2];

        Y  =       + (0.299    * R) + (0.587    * G) + (0.114    * B);

        ip[0] = Y;
        ip[1] = Y;
        ip[2] = Y;

        ip = &ip[3];
    }

    return 0;
}

