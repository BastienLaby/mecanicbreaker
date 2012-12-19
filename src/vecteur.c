#include "Vecteur.h"
#include <math.h>

/* ----- FONCTIONS ----- */

Vecteur CreerVecteur(float x, float y){
	Vecteur v;
	v.x = x;
	v.y = y;
	return v;
}

Vecteur addVecteurs(Vecteur a, Vecteur b){ 
	return CreerVecteur(a.x + b.x, a.y + b.y);
}

Vecteur subVecteurs(Vecteur a, Vecteur b){ 
	return CreerVecteur(a.x - b.x, a.y - b.y);
}
Vecteur multVecteur(Vecteur a, float s){ 
	return CreerVecteur(a.x*s, a.y*s);
}

Vecteur divVecteur(Vecteur a, float s){ 
	return CreerVecteur(a.x/s, a.y/s);
}

float produitScalaire(Vecteur a, Vecteur b){ 
	return (a.x*b.x + a.y*b.y);
}

float norme(Vecteur a){	
	return sqrt(produitScalaire(a,a));
}

Vecteur normaliser(Vecteur a){
	return CreerVecteur(a.x/norme(a), a.y/norme(a));
}
