#ifndef DEFINE_BORDURE
#define DEFINE_BORDURE

#include "Couleur.h"
#include "Texture.h"

#include <GL/gl.h>
#include <GL/glu.h>

/* ----- STRUCTURES ----- */

typedef struct {
	float abscisse;
	Texture texture;
}Bordure;

/* ----- FONCTIONS ----- */

Bordure CreerBordure(float abscisse, Texture texture);
void dessinBordure(Bordure b, float hauteur_fenetre, GLuint texture);



#endif



