#include "fonctions.h"

int main(int argc, char **argv) {
  
    int hauteur,
		**matrice = NULL,
		temps;
 
    nourriture *premiereStruct = NULL;
  
    printf("Combien de temps laissez vous à douglas pour manger le plus possible ? ");
    scanf("%d", &temps);
    //
    //- Détermine le nombre de ligne du garde_manger.txt
    //
    hauteur = nombreligne (argv[1]);
    //
    //- Charge notre structure.
    //- Vérification de l'allocation
    //
    premiereStruct = ChargerAliment(argv[1], premiereStruct, hauteur);
    if(!premiereStruct){

        printf ("Allocation structure échouée.");
    }
    //
    //- Remplissage de la matrice.
    //- Vérification de l'allocation. 
    //
    matrice = remplissage(premiereStruct, matrice, hauteur, temps);
    if(!matrice){

        printf("L'allocation de la matrice a échouée.");
    }
    //
    //- Affichage de la matrice. 
    //
    affichage(matrice, temps, hauteur);
    //
    //- Affichage des objets à prendre.
    //
    objet(matrice, premiereStruct, temps, hauteur);

    return 0;
}