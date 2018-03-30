#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>

void Echange(int* Tab,int i,int j){
	int tmp=Tab[i];
	Tab[i]=Tab[j];
	Tab[j]=tmp;
	
}
int partitionnement(int* Tab,int indiceMarqueur,int max){
	while (1){		
		if(Tab[max]<=Tab[indiceMarqueur])
			Echange(Tab,max,indiceMarqueur);						
														
		if(max<indiceMarqueur)
			max++;
			
		if(max>indiceMarqueur)
			max--;			
		
		if(max==indiceMarqueur)
			break;				
	}
	return indiceMarqueur;
}

void trisrapide(int* Tab,int i,int j){
	int p;
	if(i<j){
		p=partitionnement(Tab,i,j);
		printf("%d\n",p);
		trisrapide(Tab,i,p-1);
		trisrapide(Tab,p+1,j);		
	}	
}

void shuffle(int* Tab,int N){
	int j;
	for(int i=N-1;i>0;i--){
       j =rand() % (i + 1 - 0) + 0;
       Echange(Tab,j,i);
	   
	}
}

void InitTabPresqueTrie(int* Tab,int N,int P){
	int k,l;
	for(int i=0;i<N;i++)
		Tab[i]=i;
	affiche(Tab,N);	
	for(int j=0;j<P;j++){
		k=rand()%(N);	
		l=rand()%(N);
		Echange(Tab,k,l);
		affiche(Tab,N);
	}
	
}

void InitTabUniforme(int* Tab,int N){
	
	for(int i=0;i<N;i++)
		Tab[i]=i+1;
	
	shuffle(Tab,N);
}
void InitTabRepetition(int* Tab,int N,int R){
	
	for(int i=0;i<N;i++)
		Tab[i]=rand()%(R);	
}

void affiche(int *Tab,int N){
	int i;
	for(i=0;i<N;i++)
		printf("[%d]",Tab[i]);	
	printf("\n");	
}