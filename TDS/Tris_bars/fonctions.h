#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Sbar {
	char name[100]; // Name of the bar (no space in the string)
	float dist;// Score associated to the distance	
	float price; // Price of one shooter
}Bar;


/*************************** CreateTab() *****************************
8
Allocate a new tab and fill it with informations given by the
'
path
'
9
Returns the array, or NULL in case of failure
10
11
ARGS: char *path: path of the informations file
12
*********************************************************************/

Bar *CreateTab (char *path,int *taille);
void DisplayTab(Bar *tab,int taille);
void Lexico (Bar *Tab,int N);

void BubbleSort (Bar *tab,int N, int key);
void SelectionSort (Bar *tab,int N, int key);
void InsertionSort (Bar *tab,int N, int key);