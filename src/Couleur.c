#include "Couleur.h"

/* ----- FONCTIONS ----- */

Couleur CreerCouleur(float r, float g, float b){
	Couleur c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

Couleur addCouleurs(Couleur c1, Couleur c2){
	return CreerCouleur(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

Couleur subCouleurs(Couleur c1, Couleur c2){
	return CreerCouleur(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

Couleur multCouleurs(Couleur c1, Couleur c2){
	return CreerCouleur(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

Couleur diffCouleurs(Couleur c1, Couleur c2){
	return CreerCouleur(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);
}

Couleur multCouleurC(Couleur c, float s){	
	return CreerCouleur(c.r * s, c.g * s, c.b * s);
}

Couleur divCouleurC(Couleur c, float s){
	return CreerCouleur(c.r / s, c.g / s, c.b / s);
}
