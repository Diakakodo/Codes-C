#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#ifdef WIN32
#include <windows.h>
#endif


/* Plateau de jeu et variables globales*/
char **plateau;
int WIDTH, HEIGHT;

/* Prototypes */
void clear_screen(void);
int init_game ( void );
void draw_game ( void );
int is_in_range (int ligne, int colonne);
int nb_cases_adj (int ligne, int colonne);
int update_game ( void );
void play_game ( void );

/*************************** clear_screen() ******************************
Nettoyage de l'ecran
*************************************************************************/
void clear_screen(void)
{ 
	#ifdef WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

/**************************** init_game() ********************************
Initialisation du plateau de jeu
Retourne 0 en cas de succes, un nombre negatif en cas d'erreur

ARGS: void
*************************************************************************/
int init_game ( void )
{
	int ligne, colonne, i; // Variables de boucle
	int choix = -1; // Nombre de valeurs correctement saisies de la part de l'utilisateur
	
	// Allocation mémoire
	plateau = (char**)calloc(HEIGHT, sizeof(char*));
	for (i=0; i<HEIGHT; i++)
		plateau[i] = (char*)calloc(WIDTH, sizeof(char));
	
	// Affichage choix utilisateur
	printf ("Choisissez votre motif de base:\n\
	Ligne de 3 elements ------------> 1\n\
	U ------------------------------> 2\n\
	Glider -------------------------> 3\n\
	Aleatoire ----------------------> 4\n\
	Aleatoire symetrie horizontale -> 5\n\
	Aleatoire symetrie verticale ---> 6\n\
	Canon a planeurs ---------------> 7\n\
	Vide ---------------------------> 8\nChoix: ");
	
	scanf ("%d", &choix);
	getchar();
	while (choix < 0)
	{
		printf ("Choisir un element de la liste:\n");
		scanf ("%d", &choix);
		getchar();
	}
	switch (choix)
	{
	case 1: // Ligne de 3 elements stable
		plateau[HEIGHT/2][WIDTH/2-1] = 1;
		plateau[HEIGHT/2][WIDTH/2] = 1;
		plateau[HEIGHT/2][WIDTH/2+1] = 1;
		break;
	
	case 2: // U centre
		plateau [HEIGHT/2-1][WIDTH/2-1] = 1;
		plateau [HEIGHT/2][WIDTH/2-1] = 1;
		plateau [HEIGHT/2+1][WIDTH/2-1] = 1;
		plateau [HEIGHT/2+1][WIDTH/2] = 1;
		plateau [HEIGHT/2-1][WIDTH/2+1] = 1;
		plateau [HEIGHT/2][WIDTH/2+1] = 1;
		plateau [HEIGHT/2+1][WIDTH/2+1] = 1;
		break;
		 
	case 3: // Glider
		plateau [HEIGHT/4+1][WIDTH/4-1] = 1;
		plateau [HEIGHT/4+1][WIDTH/4] = 1;
		plateau [HEIGHT/4+1][WIDTH/4+1] = 1;
		plateau [HEIGHT/4][WIDTH/4+1] = 1;
		plateau [HEIGHT/4-1][WIDTH/4] = 1;
		break;
	
	case 4: // Aleatoire
		for (ligne=0; ligne<HEIGHT; ligne++)
			for (colonne=0; colonne<WIDTH; colonne++)
				plateau[ligne][colonne] = rand()&1;
	break;
				
	case 5: // Aleatoire symetrique vertical
		for (ligne=0; ligne<HEIGHT/2; ligne++)
			for (colonne=0; colonne<WIDTH; colonne++)
				plateau[ligne][colonne] = plateau[HEIGHT-ligne-1][colonne] = rand()&1;
	break;
		
	case 6: // Aleatoire symetrique vertical
		for (ligne=0; ligne<HEIGHT; ligne++)
			for (colonne=0; colonne<WIDTH/2; colonne++)
				plateau[ligne][colonne] = plateau[ligne][WIDTH-colonne-1] = rand()&1;
	break;
	
	case 7: // Canon a planeurs
		plateau[5][10] = plateau[5][11] = plateau[6][10] = plateau[6][11] = 1;
		plateau[5][15] = plateau[4][16] = plateau[3][17] = plateau[6][16] = plateau[7][17] = 1;
		plateau[2][19] = plateau[3][19] = plateau[8][19] = plateau[7][19] = 1;
		for (i=0; i<3; i++)
		{
			plateau [4+i][18] = 1;
			plateau [3][24+i] = 1;
			plateau [5+i][26] = 1;
			plateau [1][33+i] = 1;
			plateau [5][33+i] = 1;
			plateau [2+i][35] = 1;
			plateau [2+i][38] = 1;
		}
		plateau[5][29] = plateau[5][30] = plateau[6][30] = 1;
		plateau[7][29] = plateau[8][29] = plateau[8][28] = 1;
		plateau[0][33] = plateau[0][34] = plateau[6][33] = plateau[6][34] = 1;
		plateau[2][36] = plateau[4][36] = 1;
		plateau[3][44] = plateau[3][45] = plateau[4][44] = plateau[4][45] = 1;
		
		break;
	
	case 8: // Vide;
	break;
		
	default: // Inconnu
		printf ("Choix non encore implemente\n");
		return -1;
	}
	
	return 0;
}

/*************************** is_in_range() *******************************
TEste si la case donnee est dans le plateau de jeu
Retourne 1 si oui, 0 sinon

ARGS: int ligne, colonne; ligne colonne de la case
*************************************************************************/
int is_in_range (int ligne, int colonne)
{
	if ( (ligne >= 0) && (ligne < HEIGHT) && (colonne >= 0) && (colonne < WIDTH) )
		return 1;
	return 0; 
}

/*************************** nb_cases_adj() ******************************
Compte le nombre de cases adjacentes a la case (ligne,colonne)
Retourne le nombre de cases adjacentes, -1 en cas d'indices hors limites

ARGS: int ligne, colonne: position dans le plateau de jeu.
**************************************************************************/
int nb_cases_adj (int ligne, int colonne)
{
	int i,j; // Variables de boucle
	int posx, posy; // Position des cases adjacentes
	int adj=0;        // Nombre de cases adjacentes
	
	for (i=-1; i<=1; i++)
	{
		for (j=-1; j<=1; j++)
		{
			// case centrale, on passe
			if ((i==0) && (j==0))
				continue;
			
			// Test de la case adjacente
			posx = ligne + i;
			posy = colonne + j;
			if ((is_in_range(posx, posy)) && (plateau[posx][posy] == 1))
				adj++;
		}
	}
	
	return adj;
}

/******************************* update_game() ***************************
Mise a jour du plateau de jeu
Retourne 0, un nombre negatif en cas d'erreur

ARGS: void
*************************************************************************/
int update_game ( void )
{
	int ligne, colonne; // Variables de boucle
	char plateau_tmp[HEIGHT][WIDTH];
	
	// Parcours du plateau et mise à jour des cases
	for (ligne=0; ligne<HEIGHT; ligne++)
	{
		for (colonne=0; colonne<WIDTH; colonne++)
		{
			int adj = nb_cases_adj (ligne, colonne);

			// Cellule actuelle morte et trois voisines vivantes -> renaissance
			if ( (plateau[ligne][colonne] == 0) && (adj == 3) )
			{
				plateau_tmp[ligne][colonne] = 1;
			}
			// Cellule actuelle vivante et 2 ou 3 voisines vivantes -> vie
			else if ( (plateau[ligne][colonne] == 1) && ( (adj == 2) || (adj == 3) ) )
			{
				plateau_tmp[ligne][colonne] = 1;
			}
			// Dans les autres cas -> mort
			else
				plateau_tmp[ligne][colonne] = 0;
		}
	}
	
	// COpie du plateau temporaire
	for (ligne=0; ligne<HEIGHT; ligne++)
		for (colonne=0; colonne<WIDTH; colonne++)
			plateau[ligne][colonne] = plateau_tmp[ligne][colonne];
			
	return 0;
}

/***************************** draw_game() ******************************
Dessine le plateau de jeu
Ne renvoie rien

ARGS: void
************************************************************************/
void draw_game ()
{
	int ligne, colonne; // Variable de boucle
	
	// Nettoyage de l'ecran
	clear_screen();
	// Dessin de la ligne du haut
	printf ("\n");
	for (colonne=-1; colonne<=WIDTH; colonne++)
		printf ("-");
	printf ("\n");
	
	// Dessin du plateau
	for (ligne=0; ligne<HEIGHT; ligne++)
	{
		printf ("|");
		for (colonne=0; colonne<WIDTH; colonne++)
		{
			if (plateau[ligne][colonne] == 1)
				printf("%c", '#');
			else
				printf(" ");
		}
		printf ("|\n");
	}
	
	// Dessin de la ligne du bas
	for (colonne=-1; colonne<=WIDTH; colonne++)
		printf ("-");
	printf ("\n");
}

/********************************* play_game() *******************************
Joue le jeu de la vie
Ne renvoie rien

ARGS: void
******************************************************************************/
void play_game ( void )
{
	char play = 'y';
	int iter = 0;
	
	// Demande a l'utilisateur de continuer
	printf ("\nVoulez-vous continuer? ('n' pour arreter) ");
	scanf ("%c", &play);
	
	while (play != 'n')
	{
		iter++;
		// Mise a jour + dessin
		update_game();
		draw_game();
		
		// Demande a l'utilisateur de continuer
		printf ("\n%d iterations. Voulez-vous continuer? ('n' pour arreter) ", iter);
		scanf ("%c", &play);
	}
	
}

/*****************************************************************************/
int main ( int argc, char **argv )
{
	if(argc<3){
		printf("Il faut mettre des arguments !\n");
		return 0;
	}		
	int tmp;
	// Initialisation de l'aleatoire
	srand (time(NULL));		
	WIDTH = atoi(argv[1]);
	HEIGHT = atoi(argv[2]);
	tmp = init_game();
	if (tmp == 0)
	{
		draw_game();
		play_game();
	}
	
	return 0;
}
