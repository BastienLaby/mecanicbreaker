#ifndef DEFINE_NIVEAU
#define DEFINE_NIVEAU

#include "Brique.h"
#include "Joueur.h"
#include "Balle.h"
#include "Texture.h"

/* TAILLE DES BRIQUES */
#define HAUTEUR_BRIQUE 2.5
#define LARGEUR_BRIQUE 5

/* Structure */

typedef struct {
		Brique* briques;
		int nb_briques;
		Joueur* joueur1;
		Joueur* joueur2;
		MaillonBalle* mb1;
		MaillonBalle* mb2; 
		MaillonBalle* balles;
		Texture texture;
}Niveau;

/* Fonctions */

Niveau CreerNiveau(int nb_niveau, Joueur* j1, Joueur* j2);

#endif
