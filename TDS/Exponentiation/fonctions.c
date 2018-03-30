#include "fonctions.h"

int NbDigit(int N){
	
    int c=0;
    do{
        N/=10;
        c++;
    }while(N>0);
    return c;
}

int MirorGD(int N,int nb){
	int reste=0,puissance,puissance2,x=0,resultat=0;
	
	while(nb!=0){
		puissance=pow(10,nb-1);
		puissance2=pow(10,x);
		reste=N/puissance;
		N-=reste*puissance;
		resultat+=reste*puissance2;
		nb--;
		x++;
		
	}
	return resultat;	
}	
void NbMiroir(){
	int N,nb;
	printf("Entrez un nombre\n");
	scanf("%d",&N);
	nb=NbDigit(N);
	N=MirorGD(N,nb);
	printf("%d\n",N);	
}

unsigned int ExpoNaiveIte(unsigned int g,unsigned int e,unsigned int n){
	int i;
	unsigned int resultat=1;
	for(i=1;i<=e;i++){
		
		resultat*=g;
		resultat%=n;
	}
				
	return resultat;
}

int power_of_two(int a){
    if(a%2 != 0) return 0;
    else if(a == 2) return 1;
    else return power_of_two(a/2);
}

		

unsigned int ExpoPuiss2Rec(unsigned int g,unsigned int e,unsigned int n){
	
	if(e==1)
		return g;
	
	g%=n;
	return ExpoPuiss2Rec(g*g,e/2,n);	
}

unsigned int ExpoPuiss2(){
	
	unsigned int g=5,e=4,n=5;
		if(!power_of_two(e))
			return 0;
		g=ExpoPuiss2Rec(g,e,n);	
		printf("%d\n",g);
		return g;
	
}

int NombreBits (unsigned int n){
	
	if(n==0)
		return 0;
	return NombreBits(n>>1)+1;		
}

int *DecompoBinaire(int n,int *taille){
	int bits=NombreBits(n)-1;
	int *Dec;
	Dec=(int*)calloc(*taille,sizeof(int));
	
	for(int i=0;i<=bits;i++)
		Dec[i]=((n>>i)&1);
	return Dec;	
}

unsigned int ExpoTabulaire(unsigned int g,unsigned int e,unsigned int n){
	
	int cpt,res=1,N=NombreBits(e);
	
	int* tab=(int*) calloc(N,sizeof(int));
	int* b=(int *) calloc(N,sizeof(int));
	
	b=DecompoBinaire(e,&N);
	
	tab[0]=g;
	
	for(cpt=1;cpt<=N;cpt++){
		tab[cpt]=tab[cpt-1]*tab[cpt-1];
		tab[cpt]%=n;
	}		
	for(cpt=0;cpt<=N-1;cpt++){
		
		if(b[cpt]==1){
			res*=tab[cpt];
			res%=n;			
		}		
	}	
	return res;	
}

unsigned int ExpoRapide(unsigned int g,unsigned int e,unsigned int n){
	
	int res=1;
	while(e>0){
		
		if(e%2){
			
			res=res*g%n;
		}
		g=g*g%n;
		e/=2;
	}
	return res;
}

void porciney(char *path1,char* path2){
	
	

}
