#ifndef _LIB_IMAGE_H_
#define _LIB_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct pixel_t
{
	unsigned char B, G, R;
}pixel;
typedef pixel *pixel_p;

typedef struct HSV_t
{
	int H;
	float S, V;
}HSV;
typedef HSV *HSV_p;

typedef struct YCbCr_t
{
	unsigned char Y, Cb, Cr;
}YCbCr;
typedef YCbCr *YCbCr_p;

typedef struct image_t
{
	pixel_p rgb;
	HSV_p hsv;
	YCbCr_p luma;
	int larg, haut;
	int size;
	unsigned char header[54];
}image;
typedef image *image_p;

HSV RGBtoHSV(pixel *rgb);
YCbCr RGBtoYCbCr(pixel *rgb);

image *LireImage(char *imgpath);
int EcrireImage(image *img, char *imgpath);

void Tri_insertion(image *img);
int Comparaison(pixel_p P1,pixel_p P2);

void Tri_rapide(image* img,int i,int j);
int partitionnement(image* img,int indiceMarqueur,int max);
void Echange(image* img,int i,int j);
void Tri_bulles(img);
#endif
