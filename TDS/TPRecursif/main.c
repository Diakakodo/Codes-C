#include <stdio.h>
#include <string.h>
#include "recursif.h"
int main(){	
	int nb,res,n;;
	//char* sol=NULL;
	char str1[]="fedcbafedcba";
	int cpt=strlen(str1);
	char str2[cpt];
	char occ='j';

	float So,Ro;
	float CrSa=0.03,FacEv=0.0005,MoRe=0.06,res1,res2;
	
	printf("Tapez 1 pour connaitre la parite d\'un nombre\nTapez 2 pour voir quelle chaine apparait en premier dans le dictionnaire !\n");
	printf("Tapez 3 pour connaitre le nombre d\'occurences d\'une lettre dans un mot !\nTapez 4 pour inverser le mot !\n");
	printf("Tapez 5 pour observer le modele proie prédateur !\n");
	scanf("%d",&res);
	if(res <1 || res>5)
		return 0;
	switch(res){
		
		case 1:
			printf("Entrez un nombre et je vous dirais s\'il est pair !\n");
			scanf("%d",&nb);
			res=pair(nb);
			if(res==1)
				printf("%d est pair !\n",nb);
			else	
				printf("%d n\'est pas pair...\n",nb);
		break;
		
		case 2:			
			res=CompareChaine(str1,str2);
			switch(res){
				
				case 0:
					printf("Les chaines sont au meme endroit !\n");
					break;
				
				case 1:
					printf("%s est avant %s dans le dictionnaire !\n",str2,str1);
					break;
					
				case -1:
					printf("%s est avant %s dans le dictionnaire !\n",str1,str2);
					break;
			}				
		break;
		
		case 3:			
			res=NbOcc(str1,occ);			
			printf("Il y a %d %c dans le mot %s\n",res,occ,str1);		
		break;

		case 4:						
			str2[cpt-1]=InverserMot(str1,str2,cpt-2);			
			printf("%s\n",str2);
		break;
		
		case 5:
			printf("Sardines a l\'etat initial ? ");
			scanf("%f",&So);
			getchar();
			printf("Requins a l\'etat initial ? ");
			scanf("%f",&Ro);
			getchar();
			printf("A quel rang voulez vous observer le modele ? ");
			scanf("%d",&n);
			res1=Sardine(So,Ro,MoRe,CrSa,FacEv,n);
			res2=Requin(So,Ro,MoRe,CrSa,FacEv,n);
			printf("Il y a %f Sardines et %f Requins au rang %d\n",res1,res2,n);			
		
		break;
	}				
	return 0;
}
