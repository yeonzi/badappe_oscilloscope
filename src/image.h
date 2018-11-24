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

#ifndef _IMAGE_H_
#define _IMAGE_H_ 1

#include <stdint.h>

typedef struct {
    int32_t     magic;      /* Should Always Be 0x474D4959 */
    int32_t     width;
    int32_t     height;
    int32_t     model;
    int32_t     nChannels;
    int32_t     lStep;
    int32_t     pStep;
    float      *data;
} image_t;

/* image magic number */
#define IMG_MAGIC           0x474D4959

/* image model */
#define IMG_MODEL_CIEXYZ    0
#define IMG_MODEL_BGR       1
#define IMG_MODEL_BGRA      2
#define IMG_MODEL_YUV       3
#define IMG_MODEL_YCBCR     4
#define IMG_MODEL_HSV       5
#define IMG_MODEL_HSL       6
#define IMG_MODEL_CYMK      7
#define IMG_MODEL_GRAY      8
#define IMG_MODEL_Y         9

#define IMG_MODEL_RGB       IMG_MODEL_BGR

/* image channel rgba */
#define IMG_CHANNEL_B       0
#define IMG_CHANNEL_G       1
#define IMG_CHANNEL_R       2
#define IMG_CHANNEL_A       3

image_t * image_new(int32_t width, int32_t height, int32_t model);

inline float * image_pixel(image_t * img, int32_t x, int32_t y)
{
    return (img->data) + x * (img->pStep) + y * (img->lStep);
}

int  image_save(image_t * img, const char * path);
void image_free(image_t * img);

#endif /* _IMAGE_H_ */
