#ifndef DEFINE_BALLE
#define DEFINE_BALLE

#include "Vecteur.h"
#include "Couleur.h"
#include "Point.h"
#include "Joueur.h"
#include "Texture.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>



/* Nombre de segments pour tracer la balle */
#define SEGMENTS 1000

/* Le repere va de -40 à 40 en x, pareil en y */
#define REPERE_SIZE_X 40
#define REPERE_SIZE_Y 40

/* HAUTEUR RAQUETTE */
#define HAUTEUR_RAQUETTE 1.5

/* Maths */
#define M_PI 3.14159265

/* ----- STRUCTURES ----- */

typedef enum{
	EN_JEU,
	PERDUE,
	SUR_RAQUETTE
}EtatBalle;

typedef enum{
	NORMALE,
	SPAWN
}TypeBalle;

typedef struct {
	Point centre;
	float rayon;
	Vecteur direction;
	EtatBalle etat;
	Couleur couleur;
	Joueur* dernierJoueur;
	int id_balle;
	Texture texture;
	TypeBalle type;
}Balle;

typedef struct maillonBalle{
	Balle balle;
	struct maillonBalle* next;
}MaillonBalle;



/* ----- FONCTIONS ----- */

Balle CreerBalle(Point centre, float rayon, Vecteur direction, EtatBalle etat, Couleur couleur, Joueur* dernierJoueur, Texture texture, TypeBalle type);
void dessinBalles(MaillonBalle* liste, GLuint texture);

/* Implementation d'une liste de balles */

MaillonBalle* allouerMaillonBalle(Balle balle);
MaillonBalle* ajouterMaillonBalle(MaillonBalle* liste, Balle balle);
MaillonBalle* supprimerMaillonBalle(MaillonBalle* liste, int id_balle);
MaillonBalle* recupMaillonBalle(MaillonBalle* liste, int id_balle);
void libererListeBalle(MaillonBalle* liste);
void deplacerBalles(MaillonBalle* liste, Joueur* joueur1, Joueur* joueur2);
int nbBalles(MaillonBalle* liste);

#endif
