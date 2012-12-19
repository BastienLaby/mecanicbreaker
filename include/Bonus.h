#ifndef DEFINE_BONUS
#define DEFINE_BONUS

#include "Point.h"
#include "Vecteur.h"
#include "Joueur.h"
#include "Balle.h"
/*#include "Brique.h"*/

/* STRUCTURES */

typedef enum{
	NO_BONUS,
	UP_TAILLE_RAQUETTE,
	DOWN_TAILLE_RAQUETTE,
	UP_VITESSE_BALLE,
	DOWN_VITESSE_BALLE,
	SPAWN_BALLE,
	IMAC_I,
	IMAC_M,
	IMAC_A,
	IMAC_C
}TypeBonus;

typedef struct{
	Point centre;
	Vecteur direction;
	float largeur;
	float hauteur;
	TypeBonus typeBonus;
	int id_bonus;
}Bonus;

typedef struct sbonus{
	Bonus bonus;
	struct sbonus* next;
}MaillonBonus;



/* FONCTIONS */

Bonus CreerBonus(Point centre, Vecteur direction, float largeur, float hauteur, TypeBonus typeBonus);
void dessinBonusImac(Joueur* j1, Joueur* j2, GLuint texture);


/* Implementation d'une liste de bonus attrapables */

MaillonBonus* allouerMaillonBonus(Bonus bonus);
MaillonBonus* ajouterMaillonBonus(MaillonBonus* liste, Bonus bonus);
MaillonBonus* supprimerMaillonBonus(MaillonBonus* liste, int id_bonus);
MaillonBonus* recupMaillonBonus(MaillonBonus* liste, int id_bonus);
void libererListeBonus(MaillonBonus* liste);

float signe(float nb);
int nbElement(MaillonBonus* liste);
void afficherListe(MaillonBonus* liste);

#endif
