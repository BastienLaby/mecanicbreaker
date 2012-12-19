#include "Brique.h"
#define charSize 30


/* --- FONCTIONS --- */

Brique CreerBrique(Point centre, float largeur, float hauteur, int solidite, TypeBonus typeBonus, Couleur couleur){
	Brique b;
	b.centre = centre;
	b.largeur = largeur;
	b.hauteur = hauteur;
	b.solidite = solidite;
	b.typeBonus = typeBonus;
	b.couleur = couleur;
	
	return b;
}

Brique* CreerNiveauBriques(char* fichier, float hauteur_brique, float largeur_brique, float esp_lignes, float esp_colonnes){
	
	/* DANS UN FICHIER DE NIVEAU :
	* 1ere ligne : NB_COLONNES NB_LIGNES  												    
	* 3eme ligne : TYPES DE BONUS (une brique d'un même bonus peut avoir des solidité différentes, car un bonus, ça se mérite !)        */ 
	
	/* Ouverture du fichier */
	FILE* niveau = fopen(fichier, "r");
	if(niveau == NULL){
		printf("Fonction CreerNiveauBriques : Erreur lors de l'ouverture du fichier : %s\n", fichier);
	}
	
	/* Lecture du niveau */
	
		/* On récupère le nombre de ligne et de colonne */
		int nb_colonnes, nb_lignes;

		if (fscanf(niveau, "%d %d", &nb_colonnes, &nb_lignes) == EOF ){
			printf("END OF FILE\n");
		}
		
		if (nb_colonnes < 0 || nb_lignes < 0){
			fprintf(stderr, "Fonction CreerNiveauBrique : ERREUR - Le format de fichier de niveau est incompatible (saisissez un nombre de lignes/colonnes strictement positif)\n");
		}
		
		/* On autorise un maximum de briques en largeur et en hauteur */
		if(nb_colonnes > 15){ nb_colonnes = 15; }
		if(nb_lignes > 19){ nb_lignes = 19; }
		
		printf("%d %d\n", nb_lignes, nb_colonnes);
		
		/* Nombre de briques */
		int nb_briques = nb_colonnes*nb_lignes;		
		
		/* Allocation mémmoire des briques */
		Brique* briques = (Brique*)malloc(nb_briques*sizeof(Brique));
		
		/* coordonnée en x de la première brique */
		float coord_premiere_brique_x = - ((nb_colonnes*largeur_brique)+(nb_colonnes-1)*esp_colonnes)/2 + largeur_brique/2;
		/* coordonnée en y de la première brique */
		float coord_premiere_brique_y = ((nb_lignes*hauteur_brique)+(nb_lignes-1)*esp_lignes)/2 - hauteur_brique/2;
		
		int bonus, i,j,k;
		float x, y;
		
		/* On recupere le bonus de la brique */
		for(i=0; i<nb_briques; i++){
			if (fscanf(niveau, "%d", &bonus) == EOF){
				printf("END OF FILE\n");
			}
			configurerBrique(&briques[i], bonus);
		}
		
		k = 0;
		for (i=0; i<nb_lignes; i++){
			for(j=0; j<nb_colonnes; j++){
				/* On renseigne la position de la brique */
				x = coord_premiere_brique_x + j*(largeur_brique + esp_colonnes);
				y = coord_premiere_brique_y - i*(hauteur_brique + esp_lignes);
				briques[k].centre=CreerPoint(x,y);
				briques[k].largeur = largeur_brique;
				briques[k].hauteur = hauteur_brique;
				k++;
			}
		}

	/* Fermeture du fichier */
	if (fclose(niveau) == EOF) {
		printf("Fonction CreerNiveauBriques : échec de fermeture du fichier : %s\n", fichier);
	}
	
	return briques;

}

int nbBriques(char* fichier){
	
	/* Ouverture du fichier */
	FILE* niveau = fopen(fichier, "r");
	if(niveau == NULL){
		printf("Fonction nbBriques : Erreur lors de l'ouverture du fichier : %s\n", fichier);
	}
	
	/* On récupère le nombre de ligne et de colonne */
		int nb_colonnes, nb_lignes;

		if (fscanf(niveau, "%d %d", &nb_colonnes, &nb_lignes) == EOF ){
			printf("END OF FILE\n");
		}	
	
	/* Fermeture du fichier */
	if (fclose(niveau) == EOF) {
		printf("Fonction nbBriques : échec de fermeture du fichier : %s\n", fichier);
	}
	
	return nb_colonnes*nb_lignes;
}

void dessinBrique(Brique brique, GLuint texture){

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glPushMatrix();
		/* On positionne le repère au bon endroit */
		glTranslatef(brique.centre.x, brique.centre.y, 0);
		/* On dessine la brique */		
		
		glBegin(GL_QUADS);		
			glTexCoord2f(brique.texture.coordonnee.x, brique.texture.coordonnee.y); glVertex2f(-brique.largeur/2, brique.hauteur/2);
			glTexCoord2f(brique.texture.coordonnee.x + brique.texture.largeur, brique.texture.coordonnee.y); glVertex2f(brique.largeur/2, brique.hauteur/2);
			glTexCoord2f(brique.texture.coordonnee.x + brique.texture.largeur, brique.texture.coordonnee.y + brique.texture.hauteur); glVertex2f(brique.largeur/2, -brique.hauteur/2);
			glTexCoord2f(brique.texture.coordonnee.x, brique.texture.coordonnee.y + brique.texture.hauteur); glVertex2f(-brique.largeur/2, -brique.hauteur/2);
		glEnd();
		glColor3ub(255,255,255);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void configurerBrique(Brique* brique, int num_bonus){

	int k;
	
	switch(num_bonus){
		
		/* --- PAS DE BRIQUE --- */
		case 0 :
			brique->solidite = 0;
		break;
		
		/* --- BASIQUES --- */
		case 1 :
			brique->solidite = 1;
			brique->typeBonus = NO_BONUS;
			brique->texture.id_texture=1;
			k = 8;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 2 :
			brique->solidite = 2;
			brique->typeBonus = NO_BONUS;
			k = 9;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 3 :
			brique->solidite = 3;
			brique->typeBonus = NO_BONUS;
			k = 10;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 4 :
			brique->solidite = 4;
			brique->typeBonus = NO_BONUS;
			k = 11;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		
		/* --- UP taille raquette --- */
		case 11 :
			brique->solidite = 1;
			brique->typeBonus = UP_TAILLE_RAQUETTE;
			k = 12;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 12 :
			brique->solidite = 2;
			brique->typeBonus = UP_TAILLE_RAQUETTE;
			k = 13;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		/* --- DOWN taille raquette --- */
		case 21 :
			brique->solidite = 1;
			brique->typeBonus = DOWN_TAILLE_RAQUETTE;
			k = 14;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 22 :
			brique->solidite = 2;
			brique->typeBonus = DOWN_TAILLE_RAQUETTE;
			k = 15;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		/* --- UP vitesse balle --- */
		case 31 :
			brique->solidite = 1;
			brique->typeBonus = UP_VITESSE_BALLE;
			k = 18;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 32 :
			brique->solidite = 2;
			brique->typeBonus = UP_VITESSE_BALLE;
			k = 19;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		/* --- DOWN vitesse balle */
		case 41 :
			brique->solidite = 1;
			brique->typeBonus = DOWN_VITESSE_BALLE;
			k = 20;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 42 :
			brique->solidite = 2;
			brique->typeBonus = DOWN_VITESSE_BALLE;
			k = 21;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		/* --- SPAWN balle --- */
		case 51 :
			brique->solidite = 1;
			brique->typeBonus = SPAWN_BALLE;
			k = 17;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 52 :
			brique->solidite = 1;
			brique->typeBonus = SPAWN_BALLE;
			k = 18;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		/* --- BRIQUES IMAC --- */
		
		case 100 :
			brique->solidite = 1;
			brique->typeBonus = IMAC_I;
			k = 0;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 101 :
			brique->solidite = 1;
			brique->typeBonus = IMAC_M;
			k = 1;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 102 :
			brique->solidite = 1;
			brique->typeBonus = IMAC_A;
			k = 2;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		case 103 :
			brique->solidite = 1;
			brique->typeBonus = IMAC_C;
			k = 3;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		default :
			brique->solidite = 1;
			brique->typeBonus = NO_BONUS;
			k = 8;
			brique->texture = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
		break;
		
		/* --- BRIQUES IMAC --- */
		
		
	
	}

}

void appliquerBonusBrique(Brique* brique, Balle* balle, MaillonBalle* listeBalles){

	if(brique == NULL || balle == NULL){
		printf("Fonction appliquerBonus : Erreur lors du parametrage des pointeurs.\n");
	}
	
	Balle nouvelleBalle;
	
	switch(brique->typeBonus){
	
		case NO_BONUS :
		break;
		
		case UP_TAILLE_RAQUETTE :
			balle->dernierJoueur->raquette.largeur *= 1.25;
		break;
		
		case DOWN_TAILLE_RAQUETTE :
			balle->dernierJoueur->raquette.largeur *= 0.75;
		break;
		
		case UP_VITESSE_BALLE :
			balle->direction = multVecteur(balle->direction, 1.5);
		break;
		
		case DOWN_VITESSE_BALLE :
			balle->direction = divVecteur(balle->direction, 1.5);
		break;
		
		case SPAWN_BALLE :
			nouvelleBalle = CreerBalle(balle->centre, balle->rayon, multVecteur(balle->direction, -1), EN_JEU, CreerCouleur(255, 255, 255), balle->dernierJoueur, CreerTexture(1, CreerPoint(0.16,0), 0.14, 0.14), SPAWN);
			listeBalles = ajouterMaillonBalle(listeBalles, nouvelleBalle);
		break;
		
		case IMAC_I :
			balle->dernierJoueur->IMAC.I = 1;
		break;
		
		case IMAC_M :
			balle->dernierJoueur->IMAC.M = 1;
		break;
		
		case IMAC_A :
			balle->dernierJoueur->IMAC.A = 1;
		break;
		
		case IMAC_C :
			balle->dernierJoueur->IMAC.C = 1;
		break;
		
		default :
		break;	
	}	
}

