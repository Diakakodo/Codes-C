#include <stdio.h>
#include <stdlib.h>

#include "lib_image.h"

HSV RGBtoHSV(pixel *rgb)
{
	HSV hsv = { 0,0,0 };
	float r = rgb->R / 256.f, g = rgb->G / 256.f, b = rgb->B / 256.f;
	float max = r, min = r;

	// Recherche du max et du min
	if (b > max)
		max = b;
	if (g > max)
		max = g;

	if (b < min)
		min = b;
	if (g < min)
		min = g;

	// Hue
	if (max == min)
		hsv.H = 0;
	if (max == r)
		hsv.H = (int)(60 * (float)(g - b) / (max-min) + 360) % 360;
	if (max == g)
		hsv.H = (int)(60 * (float)(b - r) / (max - min) + 120);
	if (max == b)
		hsv.H = (int)(60 * (float)(r - g) / (max - min) + 240);

	// Saturation
	hsv.S = (max == 0 ? 0.f : 1.f - ((float)min / max));

	// Value
	hsv.V = (float)max;

	return hsv;
}

YCbCr RGBtoYCbCr(pixel *p)
{
	YCbCr luma = { 0,0,0 };
	unsigned char R = p->R, G = p->G, B = p->B;
	luma.Y = (int)(0.299*R + 0.587 * G + 0.114 * B);
	luma.Cb = (int)(-0.1687*R - 0.3313 * G + 0.5 * B + 128);
	luma.Cr = (int)(0.5*R - 0.4187 * G  - 0.0813 * B + 128);
	return luma;
}

image *LireImage(char *imgpath)
{
	image *img = NULL;
	FILE *test = NULL;
	int pad;
	int buf = 0, i, pos=0;

	if (!imgpath)
	{
		printf("Argument NULL dans LireImage\n");
		return NULL;
	}

	img = (image*)calloc(sizeof(image), 1);

	// Ouverture de l'image
	printf("Lecture de %s\n", imgpath);
	test = fopen(imgpath, "rb");
	if (!test)
	{
		printf("Impossible d'ouvrir %s\n", imgpath);
		return 0;
	}

	// Lecture du header
	fread(img->header, 54, 1, test);
	fseek(test, 18, SEEK_SET);
	fread(&img->larg, 4, 1, test);
	printf("larg= %d\n", img->larg);
	pad = (4 - (img->larg * 3 % 4)) % 4;

	fread(&img->haut, 4, 1, test);
	printf("haut= %d\n", img->haut);

	img->size = img->haut * img->larg;

	// Allocation des pixels
	img->rgb = (pixel_p)calloc(sizeof(pixel), img->size);
	img->hsv = (HSV_p)calloc(sizeof(HSV), img->size);
	img->luma = (YCbCr_p)calloc(sizeof(YCbCr), img->size);

	// Lecture des pixels
	fseek(test, 54, SEEK_SET);
	for (i = 0; i < img->haut; i++)
	{
		fread(&img->rgb[pos], 3, img->larg, test);
		fread(&buf, pad, 1, test);
		pos += img->larg;
	}

	// Conversion au systeme HSV
	for (i = 0; i < img->size; i++)
	{
		img->hsv[i] = RGBtoHSV(&(img->rgb[i]));
		img->luma[i] = RGBtoYCbCr(&(img->rgb[i]));
	}

	fclose(test);

	return img;
}

int EcrireImage(image *img, char *imgpath)
{
	FILE *output;
	int pad;
	int i;
	int pos = 0;
	int buf = 0;

	// Test des arguments
	if (!img || !imgpath)
	{
		printf("Arguent NULL dans EcrireImage\n");
		return -1;
	}

	pad = (4 - (img->larg * 3 % 4)) % 4;

	// Ecriture du header et des pixels
	output = fopen(imgpath, "wb");
	fwrite(img->header, 54, 1, output);
	for (i = 0; i < img->haut; i++)
	{
		fwrite(&img->rgb[pos], 3, img->larg, output);
		fwrite(&buf, pad, 1, output);
		pos += img->larg;
	}

	fclose(output);
	return 0;
}

int Comparaison(pixel_p P1,pixel_p P2){	
	int vP1,vP2;
		
	vP1=P1->B + P1->R + P1->G;
	vP2=P2->B + P2->R + P2->G;
	
	if (vP1>vP2) return 1;
	if (vP1<vP2) return -1;
	if (vP1==vP2) return 0;		
	return 0;
}

void Tri_insertion(image *img){	
	int i,j,size=img->size;
	pixel marqueur;	
	
	for(i=1;i<size;i++){	
		marqueur=img->rgb[i];
		 
		for(j=i;j>0 && Comparaison(&img->rgb[j-1],&marqueur)>0;j--)		
			img->rgb[j] = img->rgb[j-1];				 
        
        img->rgb[j] = marqueur;		
	}	
}

void Echange(image* img,int i,int j){
	pixel tmp=img->rgb[i];
	img->rgb[i]=img->rgb[j];
	img->rgb[j]=tmp;
	
}
int partitionnement(image* img,int indiceMarqueur,int max){
	while (1){		
		if(Comparaison(&img->rgb[max],&img->rgb[indiceMarqueur])<0)
			Echange(img,max,indiceMarqueur);						
														
		if(max<indiceMarqueur)
			max++;
			
		if(max>indiceMarqueur)
			max--;			
		
		if(max==indiceMarqueur)
			break;				
	}
	return indiceMarqueur;
}

void Tri_rapide(image* img,int i,int j){
	int p;
	if(i<j){
		p=partitionnement(img,i,j);		
		Tri_rapide(img,i,p-1);
		Tri_rapide(img,p+1,j);		
	}	
}

void Tri_bulles(img){
	
	int i,j,trie,N=img->size;
	pixel tmp;
	
	for(i=0;i<N-1;i++){
		trie=1;
		
		for(j=0;j<N-1-i;j++){
			
			if(Comparaison(&img->rgb[j],&img->rgb[j+1])>0){
				
				trie=0;
				tmp=img->rgb[j];
				img->rgb[j]=img->rgb[j+1];
				img->rgb[j+1]=tmp;
				
			}				
		}
		if(trie) return;	
	}	
}

int main(int argc, char **argv)
{
	image *img = NULL;
	
	if (argc<3){
		printf("Usage: %s <input> <output>\n   <input> chemin vers l'image d'entree\n    <output> chemin vers l'image de sortie\n", argv[0]);
		return 0;
	}
	img = LireImage(argv[1]);
	//Tri_insertion(img);	
	Tri_bulles(img);
	//Tri_rapide(img, 0, img->size - 1);
	EcrireImage(img, argv[2]);

	free(img->rgb);
	free(img->hsv);
	free(img);

	return 0;
}