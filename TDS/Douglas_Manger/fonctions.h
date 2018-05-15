#include <stdio.h>
#include <stdlib.h>

//
//- Structure représentant le garde manger. 
//
typedef struct nourriture_s{
   char nom[30];
   int poids;
   int temps;
   }nourriture;
      

//
//- Détermine le nombre de ligne d'un fichier.
//
int nombreligne (char *chemin);
//
//- Remplit un tableau de structure en fonction du fichier choisit.
//
nourriture *ChargerAliment(char* chemin, nourriture *tab, int lignes);
//
//- Affiche une matrice.
//
void affichage ( int **tab, int longueur, int hauteur );
//
//- Remplit la matrice.
//
int **remplissage ( nourriture *tab, int** matrice, int nbligne, int tempsmax );
//
//- Renvoit le maximum entre deux entiers.
//
int max ( int a, int b);
//
//- Affiche les objets à prendre.
//
void objet ( int **matrice, nourriture *tab, int j, int i);

