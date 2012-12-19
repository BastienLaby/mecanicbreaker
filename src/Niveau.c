#include "Niveau.h"

/* Fonctions */

Niveau CreerNiveau(int nb_niveau, Joueur* j1, Joueur* j2){	
	
	char* nom;

	switch(nb_niveau) {
		
		case 1 :
			nom = "levels/1.txt";
		break;

		case 2 :
			nom = "levels/2.txt";
		break;

		case 3 :
			nom = "levels/3.txt";
		break;

		case 4 :
			nom = "levels/4.txt";
		break;

		case 5 :
			nom = "levels/5.txt";
		break;
	}
	
	Brique* briques = CreerNiveauBriques(nom, HAUTEUR_BRIQUE, LARGEUR_BRIQUE, 0, 0);
	
	int nb_briques = nbBriques(nom);	
	
	/* Création des balles */
	Vecteur direction_balle1 = CreerVecteur(0, -0.6);
	Vecteur direction_balle2 = CreerVecteur(0, 0.6);
	Balle balle1 = CreerBalle(CreerPoint(0,36), 0.7, direction_balle1, SUR_RAQUETTE, CreerCouleur(200,65,32), j1, CreerTexture(1, CreerPoint(0.3,0), 0.14, 0.14), NORMALE);
	Balle balle2 = CreerBalle(CreerPoint(0,-36), 0.7, direction_balle2, SUR_RAQUETTE, CreerCouleur(200,65,32), j2, CreerTexture(1, CreerPoint(0.3,0), 0.14, 0.14), NORMALE);
	
	printf("balle en %f %f\n", balle1.centre.x, balle2.centre.y);
	
	/* Création de la liste de balles */
	
	
	MaillonBalle* listeBalles = NULL;
	listeBalles = ajouterMaillonBalle(listeBalles, balle1);
	listeBalles = ajouterMaillonBalle(listeBalles, balle2);
	MaillonBalle* mb1 = recupMaillonBalle(listeBalles, balle1.id_balle);
	MaillonBalle* mb2 = recupMaillonBalle(listeBalles, balle2.id_balle);
	
	Niveau niveau;
	niveau.briques = briques;
	niveau.nb_briques = nb_briques;
	niveau.joueur1 = j1;
	niveau.joueur2 = j2;
	niveau.mb1 = mb1;
	niveau.mb2 = mb2;
	niveau.balles = listeBalles;
	
	/* Parametrage de la texture */
	niveau.texture.id_texture = 0;
	float espace = floor((nb_niveau-1)/3);
	niveau.texture.coordonnee = CreerPoint(0.5 + espace*0.14, 0 + espace* 0.26);
	niveau.texture.largeur = 0.14;
	niveau.texture.hauteur = 0.26;
	
	return niveau;
}
