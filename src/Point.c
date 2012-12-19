#include "Point.h"

/* ----- FONCTIONS ----- */

Point CreerPoint(float x, float y){
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

Point pointPlusVecteur(Point p, Vecteur v){
	p.x += v.x;
	p.y += v.y;
	return p;
}

