#ifndef DEFINE_BRIQUE
#define DEFINE_BRIQUE

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "Couleur.h"
#include "Point.h"
#include "Bonus.h"
#include "Balle.h"
#include "Texture.h"
#include "Joueur.h"

/* ----- STRUCTURES ----- */



typedef struct{
	Point centre;
	float largeur;
	float hauteur;
	int solidite;
	TypeBonus typeBonus;
	Couleur couleur;
	Texture texture;
}Brique;

/* ----- FONCTIONS ----- */

Brique CreerBrique(Point centre, float largeur, float hauteur, int solidite, TypeBonus typeBonus, Couleur couleur);
Brique* CreerNiveauBriques(char* fichier, float hauteur_brique, float largeur_brique, float esp_lignes, float esp_colonnes);
int nbBriques(char* fichier);
void dessinBrique(Brique brique, GLuint texture);
TypeBonus typeBonus(int num_bonus);
void appliquerBonusBrique(Brique* brique, Balle* balle, MaillonBalle* listeBalles);
void configurerBrique(Brique* brique, int num_bonus);

#endif
