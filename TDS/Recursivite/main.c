#include "recursive.h"




int main(int argc, char **argv){ 
	
	int res,a,b,choix=-1;
	/*
	int D[7]={-1,-1,-1,-1,-1,7,3};
	int I[7]={-1,-1,-1,1,2,5,6};
	int A[7]={-1,-1,-1,-1,-1,-1,4};*/
	unsigned long nombre;
	unsigned int puissance;
	
	while(choix<0 || choix >7){
		system("clear");
		printf("Tapez :\n1 Pour calculer la puissance d\'un nombre\n2 Pour Calculer la factorielle d\'un nombre\n3 Pour calculer le reste de la divsion euclidienne de a par b\n");
		printf("4 Pour calculer la somme des nombres de 0 a a\n5 Pour les n lignes triangle de pascal\n6 Pour trouver le PGCD de a et b\n");
		printf("7 Pour connaitre le palindrome formé avec a\n");
		scanf("%d",&choix);		
	}	
	switch(choix){	
		
		case 1:
			
			printf("Entre un nombre : ");
			scanf("%lu",&nombre);
			printf("Elever a quelle puissance ? : ");
			scanf("%d",&puissance);
			nombre=PuissanceRec(nombre,puissance,1);
			printf("%lu\n",nombre);
			break;
			
		case 2:	
		
			printf("Entrez la factorielle que vous voulez calculer : ");
			scanf("%lu",&nombre);
			nombre=FactRec(nombre,1);
			printf("%lu\n",nombre);
			break;
		
		case 3:			
			
			printf("Entrez a : ");
			scanf("%d",&a);
			printf("Entrez b : ");
			scanf("%d",&b);
			res=DivEucRec(a,b);
			printf("Le reste de la division euclidienne de %d par %d est %d\n",a,b,res);
			break;
		
		case 4:
		
			printf("Entrez a : ");
			scanf("%d",&a);
			res=SommeRec(a,0);
			printf("La somme des nombres de 0 a %d est %d\n",a,res);
			break;

		case 5:
		
			printf("Ligne n ? :");
			scanf("%d",&a);
			AfficheTrianglePascal(a);
			break;
			
		case 6:
		
			printf("Entrez a : ");
			scanf("%d",&a);
			printf("Entrez b : ");
			scanf("%d",&b);
			res=PGCD(a,b);
			printf("Le PGCD de %d et de %d est %d\n",a,b,res);
			break;
			
		case 7:
			
			printf("Entrez a : ");
			scanf("%d",&a);
			res=Palindrome(a);
			printf("Le palindrome produit par %d est %d\n",a,res);
			break;
	}	
	return 0;
}
