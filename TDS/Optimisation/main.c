#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    int hauteur, Hpied, Lpied, NbBoules;
	int i, j;
	if(argc<2)
		return 0;
	FILE *fp=NULL;
	
	srand(time(NULL));
	
	fp = fopen (argv[1], "r");	
	if(fp==NULL)
		return 0;
	fscanf (fp, "%d %d %d %d", &hauteur, &Hpied, &Lpied, &NbBoules);
	
	while (1){
		usleep (300000);
		system("clear");
		printf("\n\n\n");
		// Dessin de la tete
		for (i=0; i<hauteur; i++){
			for(j=0; j<hauteur -i -1 + 15; j++)
				printf (" ");
				
			for (j=0; j<i*2+1; j++){
				int alea = rand()%100;
				if (alea<NbBoules){
					char coul = rand() % 2  * 6 + '1';
					char color[9] = "\033[30m";
					sprintf (color+3, "%cm", coul);
					//printf ("%s\n", color+2);
					printf ("%s", color);
					printf ("0");
					printf("\033[0m");
				}
				else{
					printf ("\033[32m");
					printf ("#");
					printf ("\033[0m");
				}
			}
			printf("\n");
		}		
		for (i=0; i<Hpied; i++){
			for (j=0; j<hauteur-Lpied/2-1 + 15; j++)
				printf(" ");
			printf ("\033[33m");
			for (j=0; j<Lpied; j++)
				printf ("|");
			printf ("\033[0m");
			printf("\n");
		}
	}
	return EXIT_SUCCESS;
	
}
