#ifndef DEFINE_COLOR
#define DEFINE_COLOR

/* ----- STRUCTURES ----- */

typedef struct {
	float r;
	float g;
	float b;
}Couleur;

/* ----- FONCTIONS ----- */

Couleur CreerCouleur(float r, float g, float b);
Couleur addCouleurs(Couleur c1, Couleur c2);
Couleur subCouleurs(Couleur c1, Couleur c2);
Couleur multCouleurs(Couleur c1, Couleur c2);
Couleur diffCouleurs(Couleur c1, Couleur c2);
Couleur multCouleurC(Couleur c, float s);
Couleur divCouleurC(Couleur c, float s);

#endif
