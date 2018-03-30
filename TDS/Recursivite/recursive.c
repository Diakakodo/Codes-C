#include "recursive.h"
unsigned long PuissanceRec(unsigned long valeur,short n,int accu){
	
	return (n==0)? accu:PuissanceRec(valeur,n-1,accu*valeur);
}

int FactRec( int N,int accu ){
	
	return (N<=1)?accu:FactRec(N-1,N*accu);
}

int DivEucRec(int a,int b){	
	
	return (a<b)?a:DivEucRec(a-b,b);	
}

int SommeRecTerm(int a,int accu){
	
	return (a<1)?accu:SommeRec(a-1,accu+a);
}

int SommeRec(int a){
	
	return (a<1)?0:a+SommeRec(a-1);
}

int CaseTriangle(int NumLig, int NumCol){	
	
	if(NumCol==1)
		return 1;
	
	if(NumCol==NumLig)
		return 1;
	
	return CaseTriangle(NumLig-1,NumCol)+CaseTriangle(NumLig-1,NumCol-1);		
}

void AfficheTrianglePascal(int NbLignes){
	int i,j;
	for(i=1;i<=NbLignes;i++){		
		for(j=1;j<=i;j++)
			printf("%d ",CaseTriangle(i,j));
		printf("\n");	
	}	
}

int PGCD(int a, int b){
	
	int res=DivEucRec(a,b);	
	return (res!=0)?PGCD(b,res):b;
}

int MiroirIter(int n){
	int miroir=0,*p_miroir=&miroir;
	while(n>0){
		*p_miroir=*p_miroir*10+n%10;
		n/=10;
	}
	return miroir;
}

int MiroirRecTerm(int n, int acc){
		
	return (n==0)?acc:MiroirRecTerm(n/10,acc*10+n%10);	
}

int NbChiffres(int n){
	
   int chiffre=0;
    while(n>0){
        n/=10;
        chiffre++;
	}
    return chiffre;
}
	
int Palindrome(int n){
	
    return (n/10)*PuissanceRec(10,NbChiffres(n),1)+MiroirRecTerm(n,0);
}

/*
void Hanoi(int n,int D[],int A[],int I[]){
	int i=0,stock;	
	if(n!=0){		
		Hanoi(n-1,D,I,A);
		while(D[i]=-1){	
			//printf("%d",D[i]);
			i++;
			stock=D[i];
		}
		D[i]=-1;
		i=6;
		while((((A[i])!=-1))){			
			i--;			
		}			
		A[i]=stock;			
		Hanoi(n-1,A,I,D);
		
		for(i=0;i<6;i++)
			printf("[%d]",A[i]);		
	}	
}*/

