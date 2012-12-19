#ifndef DEFINE_RAQUETTE
#define DEFINE_RAQUETTE

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Point.h"
#include "Couleur.h"
#include "Texture.h"

/* Le repere va de -40 à 40 en x, pareil en y */
#define REPERE_SIZE_X 40
#define REPERE_SIZE_Y 40

/* ----- STRUCTURES ----- */

typedef struct {
	Point centre;
	float largeur;
	float hauteur;
	Texture texture_raquette;
	Texture texture_roue;
}Raquette;

/* ----- FONCTIONS ----- */

Raquette CreerRaquette(Point centre, float largeur, float hauteur, Texture texture_raquette, Texture texture_roue);
void deplacerRaquette(Raquette* r, int sens);
void dessinRaquette(Raquette r, int joueur, GLuint texture_raquette, float alpha);

#endif
