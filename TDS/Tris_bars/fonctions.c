#include "fonctions.h"

Bar *CreateTab (char *path,int *taille){
	(*taille) = 1;
	Bar *tab=NULL;
	int i,c,N=(*taille);	
	
	FILE *fichier=fopen(path,"r");
	if(!fichier)
		return NULL;
		
	
	while((c=getc(fichier))!=EOF){		
		if(c=='\n')
			N++;
	}	
	fseek(fichier,0,SEEK_SET);		
	tab=(Bar*) calloc(N,sizeof(Bar));
	for(i=0;i<N;i++){
		
		fscanf(fichier,"%s %f %f\n",tab[i].name,&tab[i].dist,&tab[i].price);
	}
	fclose(fichier);
	(*taille)=N;
	return tab;	
}

void DisplayTab(Bar *tab,int taille){
	
	for(int i=0;i<taille;i++){
		printf("%s %f %f\n",tab[i].name,tab[i].dist,tab[i].price);
	}	
}

void Lexico (Bar *Tab,int N){	
	int i,j;
	Bar tmp;
	
	for(i=0;i<N-1;i++){		
		for(j=0;j<N-1-i;j++){			
			if(Tab[j].dist>Tab[j+1].dist){
				
				tmp=Tab[j];
				Tab[j]=Tab[j+1];
				Tab[j+1]=tmp;				
			}
			if(Tab[j].dist==Tab[j+1].dist){
				if(Tab[j].price>Tab[j+1].price){
					
					tmp=Tab[j];
					Tab[j]=Tab[j+1];
					Tab[j+1]=tmp;					
				}			
			}
		}		
	}	
}

void BubbleSort (Bar *tab,int N, int key){	
	int i,j;
	Bar tmp;
	
	if(!key){
		for(i=0;i<N-1;i++){		
			for(j=0;j<N-1-i;j++){			
				if(tab[j].dist>tab[j+1].dist){
					
					tmp=tab[j];
					tab[j]=tab[j+1];
					tab[j+1]=tmp;				
				}				
			}	
		}			
	}
}	

void SelectionSort (Bar *tab,int N, int key){
	
	int i,j,indexe=0;	
	Bar tmp,min;
	
	if(!key){							
		for(i=0;i<N;i++){
		
			min=tab[i];
			indexe=i;
			for(j=i;j<N;j++){			
				if(tab[j].dist<min.dist){	
					
					min=tab[j];
					indexe=j;
				}						
			}		
			tmp=min;
			tab[indexe]=tab[i];
			tab[i]=tmp;		
		}	
	}else{		
		for(i=0;i<N;i++){
		
			min=tab[i];
			indexe=i;
			for(j=i;j<N;j++){			
				if(tab[j].price<min.price){	
					
					min=tab[j];
					indexe=j;
				}						
			}		
			tmp=min;
			tab[indexe]=tab[i];
			tab[i]=tmp;		
		}			
	}			
}

void InsertionSort (Bar *tab,int N, int key){
	
	int i,j;
	Bar marqueur;
	
	if(!key){
		for(i=1;i<N;i++){		
			marqueur=tab[i];
			 
			for(j=i;j>0 && tab[j-1].dist>marqueur.dist;j--)			
				tab[j] = tab[j-1];				         
			tab[j] = marqueur;		
		}	
	}else{
		for(i=1;i<N;i++){		
			marqueur=tab[i];
			 
			for(j=i;j>0 && tab[j-1].price>marqueur.price;j--)			
				tab[j] = tab[j-1];				         
			tab[j] = marqueur;		
		}				
	}	
}