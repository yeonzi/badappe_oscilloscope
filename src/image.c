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
#include <string.h>
#include <image.h>

image_t * image_new(int32_t width, int32_t height, int32_t model)
{
    image_t * img = NULL;

    img = malloc( sizeof( image_t ) ); 
    if( img == NULL ) {
        perror("Cannot alloc memory for new image object");
        return NULL;
    }

    img->magic  = IMG_MAGIC;
    img->width  = width;
    img->height = height;
    img->model  = model;
    img->data   = NULL;

    switch (img->model) {
        case IMG_MODEL_CYMK:
        case IMG_MODEL_BGRA:
            img->nChannels = 4;
            break;
        default:
            img->nChannels = 3;
    }

    img->pStep = img->nChannels;
    img->lStep = img->pStep * img->width;
    img->data = malloc(img->width * img->height * img->pStep * sizeof(float));
    if ( img->data == NULL ) {
        perror("Cannot alloc memory for new image object");
        free(img);
        return NULL;
    }

    memset(img->data, 0, img->width * img->height * img->pStep * sizeof(float));

    return img;
}

void image_free(image_t * img)
{
    do {
        if (img == NULL) break;
        if (img->data != NULL) free(img->data);
        free(img);
        img = NULL;
    } while (0);
}
