#ifndef DEFINE_JOUEUR
#define DEFINE_JOUEUR

#include "Raquette.h"

/* ----- STRUCTURES ----- */
typedef struct{
	int I;
	Texture texI;
	int M;
	Texture texM;
	int A;
	Texture texA;
	int C;
	Texture texC;
}Imac;

typedef struct{
	Raquette raquette;
	int nb_vies;
	Imac IMAC;
}Joueur;



/* ----- FONCTIONS ----- */
Joueur CreerJoueur(Raquette raquette, int nb_vies);
void dessinVies(Joueur j1, Joueur j2, GLuint texture, Texture t_vie);

#endif
