#include "fonctions.h"

//
//- Affiche les objets à prendre.
//
void objet(int **matrice, nourriture *tab, int j, int i){
    //
    //- Redimension des dimensions pour adapter à la matrice.
    //
    i--;
    j--;
    //
    //- Remontée.
    //
    while(matrice[i][j] == matrice[i][j-1]){    
        
        j--;
	}        
    while(j > 0){
        
        while((i > 0) && (matrice[i][j] == matrice[i-1][j])){
            
            i--;
        }
            
        j = j - tab[i].temps;
        
        if(j > -1){
        
            printf("\nIl faut manger l'aliment : %s\n", tab[i].nom);
        }
        i--;
    }
}
//
//- Compare deux entiers pour retourner le maximum.
//
int max(int a, int b){

    if(a >= b){        
        return a;
    }    
    else{        
        return b;
    }
}
//
//- Affichage de la matrice.
//
void affichage(int **tab, int longueur, int hauteur ){

    int i = 0,
		j = 0;
    
    for(i = 0; i < hauteur; i++){
    
		printf ("ligne : %d |", i);
        for(j = 0; j < longueur; j++){
        
			printf ("%d\t", tab[i][j]);
        }
		printf("\n");
    }
}
//
//- Remplissage de la matrice.
//
int **remplissage(nourriture *tab, int** matrice, int nbligne, int tempsmax ){
   
    int i = 0,
		j = 0;
   
    matrice = (int**) calloc (nbligne, sizeof(int*));
    for(i = 0; i < nbligne; i++){
    
        matrice[i] = (int*) calloc (tempsmax, sizeof (int));
    }
    if(!matrice){
    
		printf ("Mémoire de la matrice mal alouée");
    }    
    //
    //- Début du remplissage en fonction des dimensions et de la structure donnée.
    //- Première ligne alloué
    //
    for(j = 0; j < tempsmax; j++){

        if(tab[0].temps > j){
        
            matrice[0][j] = 0;
        }
        else {
        
            matrice[0][j] = tab[0].poids;
        }
    }
    //
    //- Les autres lignes sont allouées en fonction de la première.
    //
    for(i = 1 ; i < nbligne ; i++){
    
        for(j = 0; j < tempsmax ; j++){
            
            if(tab[i].temps > j){
            
                matrice[i][j] = matrice[i-1][j];
            }
            else{
            
				matrice[i][j] = max(matrice[i-1][j], matrice[i-1][j - tab[i].temps] + tab[i].poids);
            }
        }
    }
    
    return matrice;
}
//
//- Compte le nombre de ligne du fichier.
//
int nombreligne(char *chemin){
    
    int i = 0,
		carac = 0;
    
    FILE* fichier = NULL;
    fichier = fopen(chemin,"r");
    if(!fichier){
    
    printf("Le fichier n\'a pas pu s\'ouvrir.\n");
    }
    //
    //- Stock le nombre de ligne de notre .txt dans i.
    //
    while(carac != EOF){
    
        carac = fgetc(fichier);
        if(carac == '\n'){
            
            i++;
        }
    }
    return i;
}

nourriture *ChargerAliment(char* chemin, nourriture *tab, int lignes){
   
    int i = 0;  
    FILE* fichier = NULL;
    fichier = fopen(chemin,"r");
	
	if(!fichier){		
		
		printf("Le fichier n'a pas pu s'ouvrir correctement veuillez réessayer");		
	}
    //     
    //- Allocation du tableau en fonction du nombre de ligne et du type de la structure (nourriture).
    //- Remise du pointeur en haut du fichier. 
    //- Puis vérification de l'allocation mémoire du tableau. 
    //
    fseek(fichier,0,SEEK_SET); 
    tab = (nourriture*) calloc (lignes, sizeof(nourriture)); 
    if(!tab){
		
        free(fichier);
        printf ("La mémoire allouée pour le tableau a été mal réalisée.");
    }
    //   
    //- on récupère chaques lignes du fichier pour les stocker dans le tableau de structure. 
    //
	for(i = 0; i < lignes; i++){        
		
		fscanf(fichier,"%s %d %d", tab[i].nom, &tab[i].poids, &tab[i].temps);
		printf("%d - %s, %d kg, %d minutes\n\n", i, tab[i].nom, tab[i].poids, tab[i].temps);
	}       
    //
    //- Retourne le tableau de structure chargé. 
    //
    return tab;
}