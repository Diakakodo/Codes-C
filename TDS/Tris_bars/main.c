#include <stdio.h>
#include "fonctions.h"
#define key 0

int taille=0;
char * path=NULL;

int main(int argc, char **argv)
{
	if(argc<2)
		return 0;
	path=argv[1];	
	Bar* tab=CreateTab(path,&taille);
	Bar* copy=malloc(taille*sizeof(Bar));
	
	printf("Liste de base\n");
	DisplayTab(tab,taille);
	printf("\n");
	
	memcpy(copy,tab,taille*sizeof(Bar));	
	BubbleSort(copy,taille,key);
	printf("Bubblesort\n");
	DisplayTab(copy,taille);
	printf("\n");
	
	memcpy(copy,tab,taille*sizeof(Bar));
	printf("Selectionsort\n");
	SelectionSort(copy,taille,key);
	DisplayTab(copy,taille);
	printf("\n");
	
	memcpy(copy,tab,taille*sizeof(Bar));
	printf("Insertionsort\n");
	InsertionSort(copy,taille,key);	
	DisplayTab(copy,taille);
	printf("\n");

	free(tab);
	free(copy);
	return 0;
}
