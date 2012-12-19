#include "Balle.h"
#include <time.h>

int cpt_balles = 0;

/* ----- FONCTIONS ----- */

Balle CreerBalle(Point centre, float rayon, Vecteur direction, EtatBalle etat, Couleur couleur, Joueur* dernierJoueur, Texture texture, TypeBalle type){
	Balle b;
	
	b.centre = centre;
	b.rayon = rayon;
	b.direction = direction;
	b.etat = etat;
	b.couleur = couleur;
	b.dernierJoueur = dernierJoueur;
	b.id_balle = cpt_balles +1;
	cpt_balles ++;
	b.texture = texture;
	b.type = type;
	
	return b;
}

void dessinBalles(MaillonBalle* liste, GLuint texture){

	while(liste != NULL){

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
		glPushMatrix();
			/* On positionne le repère au bon endroit */
			glTranslatef(liste->balle.centre.x, liste->balle.centre.y, 0);
			
			/* On dessine la balle */		
			glBegin(GL_QUADS);		
				glTexCoord2f(liste->balle.texture.coordonnee.x, liste->balle.texture.coordonnee.y);
					glVertex2f(-liste->balle.rayon, liste->balle.rayon);
				glTexCoord2f(liste->balle.texture.coordonnee.x + liste->balle.texture.largeur, liste->balle.texture.coordonnee.y);
					glVertex2f(liste->balle.rayon, liste->balle.rayon);
				glTexCoord2f(liste->balle.texture.coordonnee.x + liste->balle.texture.largeur, liste->balle.texture.coordonnee.y + liste->balle.texture.hauteur);
					glVertex2f(liste->balle.rayon, -liste->balle.rayon);
				glTexCoord2f(liste->balle.texture.coordonnee.x, liste->balle.texture.coordonnee.y + liste->balle.texture.hauteur);
					glVertex2f(-liste->balle.rayon, -liste->balle.rayon);
			glEnd();
			glColor3ub(255,255,255);
		glPopMatrix();
		
		glBindTexture(GL_TEXTURE_2D, 0);
		liste = liste->next;
	}
}




/* Implementation d'une liste de balles */

/* Fonction qui alloue un espace mémoire pour stocker une balle passée en parametre */
MaillonBalle* allouerMaillonBalle(Balle balle){
	MaillonBalle* nouvelleBalle = (MaillonBalle*)malloc(sizeof(MaillonBalle));
	if(nouvelleBalle == NULL){
		printf("Fonction allouerMaillonBalle : echec de l'allocation mémoire.\n");
	}
	nouvelleBalle->balle = balle;
	nouvelleBalle->next = NULL;
	return nouvelleBalle;
}

/* Fonction qui ajoute (en tête) une balle à la liste, et qui renvoie le pointeur la tête de cette liste */
MaillonBalle* ajouterMaillonBalle(MaillonBalle* liste, Balle balle){
	
	MaillonBalle* nouveauMaillon = allouerMaillonBalle(balle);
	
	/* Si la liste est vide */
	if(liste==NULL){
		return nouveauMaillon;
	}
	
	MaillonBalle* tmp = liste;
	
	/* On récupère le dernier élément de la liste */
	while(liste->next != NULL){
		liste = liste->next;
	}
	
	/* On ajoute le nouveau maillon */
	liste->next = nouveauMaillon;
	
	return tmp;
}

/* Fonction qui supprimer une balle de la liste en fonction de son ID */
MaillonBalle* supprimerMaillonBalle(MaillonBalle* liste, int id_balle){
	
	/* Si la liste est vide */
	if(liste==NULL){
		printf("Fonction supprimerMaillonBalle : la liste est vide, il n'y a rien à supprimer.\n");
		return NULL;
	}
	
	MaillonBalle* tmp = liste;
	
	/* Si le premier élément est celui à supprimer */
	if(liste->balle.id_balle == id_balle){
		tmp = liste->next;
		free(liste);
		return tmp; 
	}
	
	/* Sinon, on cherche le bon maillon à supprimer */
	while(liste->next->balle.id_balle != id_balle && liste->next != NULL){
		liste = liste->next;
	}
	
	if(liste == NULL){
		printf("Fonction supprimerMaillonBalle : l'élement à supprimer n'existe pas.\n");
		return tmp;
	}
	
	/* On enregistre l'adresse de l'element à supprimer */
	MaillonBalle* tmp2 = liste->next;
	/* On met à jour l'element suivant */
	liste->next = liste->next->next;
	/* On free l'element à supprimer */
	free(tmp2);
	/* On retourne la tête de liste */
	return tmp;	
}

/* Fonction qui renvoie le pointeur sur le maillon contenant la balle demandée */
MaillonBalle* recupMaillonBalle(MaillonBalle* liste, int id_balle){
	
	/* Si la liste est vide */
	if(liste == NULL){
		printf("Fonction recupMaillonBalle : La liste est vide, il n'y a rien à récupérer.\n");
		return NULL;
	}
	
	/* On cherche la balle */
	while(liste->balle.id_balle != id_balle && liste != NULL){
		liste = liste->next;		
	}
	
	if(liste == NULL){
		printf("Fonction recupMaillonBalle : La liste ne contient pas l'élément demandé.\n");
		return NULL;
	}
	
	return liste;
}

/* Fonction qui libère l'espace mémoire de toute la liste de balles */
void libererListeBalle(MaillonBalle* liste){

	if(liste != NULL){
		libererListeBalle(liste->next);
		free(liste);
	}
	
	
}

/* Déplace toutes les balles de la liste suivant leur vecteur directeur */
void deplacerBalles(MaillonBalle* liste, Joueur* joueur1, Joueur* joueur2){
	if(liste!=NULL){
	
		MaillonBalle* debutListe = liste;
	
		while(liste!=NULL){
	
			/* Si la balle est en jeu */
			if(liste->balle.etat == EN_JEU){
		
				/* Deplacement de la balle en fonction de son vecteur directeur */
				liste->balle.centre.x += (liste->balle.direction.x);
				liste->balle.centre.y += (liste->balle.direction.y);
	
				/* Si la balle sort en haut */
				if (liste->balle.centre.y > REPERE_SIZE_Y){
					joueur1->nb_vies --;
					liste->balle.etat = PERDUE;
		
					/* Si c'est une spawn ball, on la supprime */
					if(liste->balle.type == SPAWN){
						debutListe = supprimerMaillonBalle(debutListe, liste->balle.id_balle);
					}				
				}

				/* Si la balle sort en bas */
				if (liste->balle.centre.y < -REPERE_SIZE_Y){
					joueur2->nb_vies --;
					liste->balle.etat = PERDUE;
		
					/* Si c'est une spawn ball, on la supprime */
					if(liste->balle.type == SPAWN){
						debutListe = supprimerMaillonBalle(debutListe, liste->balle.id_balle);
					}				
				}

			}
			
		liste = liste->next;
		}
	}
}

/* Fonction qui renvoit le nombre de balles dans la liste */
int nbBalles(MaillonBalle* liste){
	
	int nb_balles = 0;
	
	while(liste != NULL){
		nb_balles +=1;
		liste = liste->next;
	}
	
	return nb_balles;
}









