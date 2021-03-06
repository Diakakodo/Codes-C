#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sdl_stuff.h"
#include "fpstimer.h"
#include "vecteur.h"

typedef struct Balle_decl{
	
	float masse; 		 	  // Kg
	float coeffriction; 	 // (sans unite)
	float attenuation;		// (Sans unite)
	Vecteur position;  		// En metres
	Vecteur vitesse;  	   // En metres / sec
	Vecteur acceleration; // En metres / sec / sec
}Balle;


// Retourne une structure Balle initalisée avec les valeurs du fichier de configuration
Balle chargerBalle(char* chemin);


// Met a jour la position de la balle en appliquant le PFD
// Retourne -1 si balle est NULL (securite)
int majPosition(Balle * balle,float dt);