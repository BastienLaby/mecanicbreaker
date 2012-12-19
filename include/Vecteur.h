#ifndef DEFINE_VECTOR
#define DEFINE_VECTOR

/* ----- STRUCTURES ----- */

typedef struct{
	float x;
	float y;
}Vecteur;

/* ----- FONCTIONS ----- */


Vecteur CreerVecteur(float x, float y);
Vecteur addVecteurs(Vecteur a, Vecteur b);
Vecteur subVecteurs(Vecteur a, Vecteur b);
Vecteur multVecteur(Vecteur a, float s);
Vecteur divVecteur(Vecteur a, float s);
float produitScalaire(Vecteur a, Vecteur b);
float norme(Vecteur a);
Vecteur normaliser(Vecteur a);

#endif
