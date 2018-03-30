#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int MirorGD(int N,int nb);
int NbDigit(int N);

void NbMiroir();

int power_of_two(int a);
unsigned int ExpoNaiveIte(unsigned int g,unsigned int e,unsigned int n);
unsigned int ExpoPuiss2Rec(unsigned int g,unsigned int e,unsigned int n);
unsigned int ExpoPuiss2();
unsigned int ExpoTabulaire(unsigned int g,unsigned int e,unsigned int n);
int NombreBits (unsigned int n);
int *DecompoBinaire(int n,int *taille);	

unsigned int ExpoRapide(unsigned int g,unsigned int e,unsigned int n);

void porciney(char *path1,char* path2);