# include "fonctions.h"

int main(int argc,char** argv){
	int res;
	unsigned int secret=28757,expop=26985,modn=65519,kinit=ExpoRapide(secret,expop,modn);
	
	unsigned int a=1103515245,b=12345,n=2147483648,k=(a*kinit+b)%n,c;

	
	if(argc<3)
		return 0;
		
	FILE *fichier1 = fopen(argv[1],"rb");
	FILE *fichier2 = NULL;
	
	if(!fopen(argv[2],"rb")){
		fichier2 = fopen(argv[2],"wb");
		
	}
	else{
		printf("Le fichier \"%s\" existe deja, voulez vous le remplacer ?\nOui 1\nNon 0\n",argv[2]);
		scanf("%d",&res);
		if(res){
			fichier2 = fopen(argv[2],"wb");
			
		}
	}

	while(!feof(fichier1)){
		
		fread(&res,1,1,fichier1);
		c=k^res;
		fwrite(&c,1,1,fichier2);
		k=(a*k+b)%n;		
	}
	fclose(fichier1);
	fclose(fichier2);
	return 0;
}	