#ifndef DEFINE_TEXTURE
#define DEFINE_TEXTURE

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#include "Point.h"

/* Nombre de segments pour tracer la balle */
#define SEGMENTS 1000
/* Maths */
#define M_PI 3.14159265

/* Structure */

typedef struct{
	/* L'id de la tileset */
	int id_texture;	
	/* Le point en haut à gauche */
	Point coordonnee;	
	/* Largeur et Hauteur (en %)*/
	float largeur;
	float hauteur;
}Texture;

/* Fonctions */

Texture CreerTexture(int id_texture, Point coord, float largeur, float hauteur);

GLenum getFormat(SDL_Surface* p);
GLuint* chargementImagesTheme1();
GLuint* chargementImagesTheme2();

void dessinCercle(int full);
void dessinRepere();
void dessinCarre(int full);
void dessinEngrenage1();
void dessinEngrenage2();

#endif
