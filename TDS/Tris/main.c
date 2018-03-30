#include "fonctions.h"
#include "dichotomie.h"
int comparaisons=0,echanges=0;

void trisbulle(int* Tab,int N){
	int i,j,tmp,trie,comparaisons=0,echanges=0;
	
	for(i=0;i<N-1;i++){
		trie=1;
		comparaisons++;
		for(j=0;j<N-1-i;j++){
			comparaisons++;
			if(Tab[j]>Tab[j+1]){
				comparaisons++;
				trie=0;
				tmp=Tab[j];
				Tab[j]=Tab[j+1];
				Tab[j+1]=tmp;
				echanges++;
			}				
		}
		if(trie){
			printf("Trisbulle : %d comparaisons %d echanges\n",comparaisons,echanges);
			return;	
			
		}	
	}
}

void triselection(int* Tab,int N){
	
	int i=0,j=0,min,indexe=0,tmp=0,trie,comparaisons=0,echanges=0;
	for(i=0;i<N;i++){
		comparaisons++;
		trie=1;
		min=Tab[i];
		indexe=i;
		for(j=i;j<N;j++){
			comparaisons++;
			if(Tab[j]<min){	
				comparaisons++;
				trie=0;
				min=Tab[j];
				indexe=j;
			}						
		}
		if(trie){
			printf("Triselection : %d comparaisons %d echanges\n",comparaisons,echanges);
			return;
			
		}
		tmp=min;
		Tab[indexe]=Tab[i];
		Tab[i]=tmp;	
		echanges++;
	}	
}

void trisinsertion(int* Tab,int N){
	
	int i,j,marqueur,comparaisons=0,echanges=0;
	for(i=1;i<N;i++){
		comparaisons++;
		marqueur=Tab[i];
		 
		for(j=i;j>0 && Tab[j-1]>marqueur;j--){	
			comparaisons+=2;
			Tab[j] = Tab[j-1];
			
		}
		 
        
        Tab[j] = marqueur;
		echanges++;
	}
	printf("Trisinsertion : %d comparaisons %d echanges\n",comparaisons,echanges);
}

int main(int argc, char **argv){
	int Tab[10000];
	for(int i=0;i<10;i++){
		InitTabUniforme(Tab,10000);
		trisbulle(Tab,10000);
		
	}
	for(int i=0;i<10;i++){
		InitTabUniforme(Tab,10000);
		triselection(Tab,10000);
		
	}
	for(int i=0;i<10;i++){
		InitTabUniforme(Tab,10000);
		trisinsertion(Tab,10000);
		
	}

	
	return 0;
	
}
