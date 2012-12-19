#ifndef DEFINE_POINT
#define DEFINE_POINT

#include "Vecteur.h"

/* ----- STRUCTURES ----- */

typedef struct {
	float x;
	float y;
}Point;

/* ----- FONCTIONS ----- */

Point CreerPoint(float x, float y);
Point pointPlusVecteur(Point p, Vecteur v);

#endif
