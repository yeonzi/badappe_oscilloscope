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
#include <string.h>
#include <math.h>
#include <image_edge_dect.h>
#include <image.h>


int image_edge_dect(image_t * img)
{
	int x0,y0;

	float conv_tmp;
	float * img_tmp;

	static image_t * img_out = NULL;

	if (img_out == NULL) {	
		img_out = image_new(img->width, img->height, IMG_MODEL_BGR);
	}

	for(x0 = 1; x0 < img->width - 1; x0++){
        for(y0 = 1; y0 < img->height - 1; y0++){
            /* ergodic pixel in image */
            conv_tmp = 0;

            conv_tmp += image_pixel(img, x0 + 1, y0)[0];
            conv_tmp += image_pixel(img, x0 + 1, y0 + 1)[0];
            conv_tmp += image_pixel(img, x0 + 1, y0 - 1)[0];
            conv_tmp += image_pixel(img, x0, y0 + 1)[0];

            conv_tmp -= image_pixel(img, x0 - 1, y0)[0];
            conv_tmp -= image_pixel(img, x0 - 1, y0 - 1)[0];
            conv_tmp -= image_pixel(img, x0 - 1, y0 + 1)[0];
            conv_tmp -= image_pixel(img, x0, y0 - 1)[0];
            
            conv_tmp = (float)fabs(conv_tmp / 8.0);

            img_tmp  = image_pixel(img_out, x0, y0);

            img_tmp[0] = conv_tmp;
            img_tmp[1] = conv_tmp;
            img_tmp[2] = conv_tmp;
            
        }
    }

    memcpy(img->data, img_out->data, 3 * img->width * img->height * sizeof(float));

	return 0;
}
