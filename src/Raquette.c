#include "Raquette.h"


/* ----- FONCTIONS ----- */

Raquette CreerRaquette(Point centre, float largeur, float hauteur, Texture texture_raquette, Texture texture_roue){
	
	
	
	Raquette r;
	r.centre = centre;
	r.largeur = largeur;
	r.hauteur = hauteur;
	r.texture_raquette = texture_raquette;
	r.texture_roue = texture_roue;
	
	return r;
}

void dessinRaquette(Raquette r, int joueur, GLuint texture, float alpha){
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
		/* On dessine la roue de gauche */
		
		glPushMatrix();
			glTranslatef(r.centre.x + r.largeur/2.2, r.centre.y, 0);
			glRotatef(alpha, 0, 0, 1);
			glScalef(3, 3, 1);
			
			glBegin(GL_QUADS);
			
				glTexCoord2f(r.texture_roue.coordonnee.x , r.texture_roue.coordonnee.y);
					glVertex2f(-0.5, 0.5);
				glTexCoord2f(r.texture_roue.coordonnee.x + r.texture_roue.largeur, r.texture_roue.coordonnee.y);
					glVertex2f(0.5,0.5);
				glTexCoord2f(r.texture_roue.coordonnee.x + r.texture_roue.largeur, r.texture_roue.coordonnee.y + r.texture_roue.hauteur);
					glVertex2f(0.5,-0.5);
				glTexCoord2f(r.texture_roue.coordonnee.x, r.texture_roue.coordonnee.y + r.texture_roue.hauteur);
					glVertex2f(-0.5, -0.5);
				
			glEnd();
		glPopMatrix();
		
		/* On dessine la roue de droite */
		
		glPushMatrix();
			glTranslatef(r.centre.x - r.largeur/2.2, r.centre.y, 0);
			glRotatef(-alpha, 0, 0, 1);
			glScalef(3, 3, 1);
			
			glBegin(GL_QUADS);
			
				glTexCoord2f(r.texture_roue.coordonnee.x , r.texture_roue.coordonnee.y);
					glVertex2f(-0.5, 0.5);
				glTexCoord2f(r.texture_roue.coordonnee.x + r.texture_roue.largeur, r.texture_roue.coordonnee.y);
					glVertex2f(0.5,0.5);
				glTexCoord2f(r.texture_roue.coordonnee.x + r.texture_roue.largeur, r.texture_roue.coordonnee.y + r.texture_roue.hauteur);
					glVertex2f(0.5,-0.5);
				glTexCoord2f(r.texture_roue.coordonnee.x, r.texture_roue.coordonnee.y + r.texture_roue.hauteur);
					glVertex2f(-0.5, -0.5);
				
			glEnd();
		glPopMatrix();
		
		/* On dessine la raquette */
		glPushMatrix();
				/* Si on dessine la raquette du joueur 1 */
				if(0 == joueur){
					glTranslatef(r.centre.x, r.centre.y, 0);
				}
				/* Si on dessine la raquette du joueur 2 */
				if(1 == joueur){
					glTranslatef(r.centre.x, r.centre.y, 0);
				}
				
					
			
			glScalef(r.largeur, r.hauteur, 1);
		
			glBegin(GL_QUADS);		
				glTexCoord2f(r.texture_raquette.coordonnee.x + r.texture_raquette.largeur, r.texture_raquette.coordonnee.y);
					glVertex2f(-0.5,0.5);
				glTexCoord2f(r.texture_raquette.coordonnee.x + r.texture_raquette.largeur, r.texture_raquette.coordonnee.y + r.texture_raquette.hauteur);
					glVertex2f(0.5,0.5);
				glTexCoord2f(r.texture_raquette.coordonnee.x, r.texture_raquette.coordonnee.y + r.texture_raquette.hauteur);
					glVertex2f(0.5, -0.5);
				glTexCoord2f(r.texture_raquette.coordonnee.x , r.texture_raquette.coordonnee.y);
					glVertex2f(-0.5, -0.5);
			glEnd();
			glColor3ub(255,255,255);
		glPopMatrix();
		
		glBindTexture(GL_TEXTURE_2D, 0);

}

void deplacerRaquette(Raquette* r, int sens){
	
	/* Test de validité du pointeur */
	if(r==NULL){
		fprintf(stderr, "Fonction mooveRaquette : problème lors du parametrage du pointeur Raquette \n");
		exit(1);
	}
	
	/* Test du sens */
	switch(sens){
	
		/* à droite : 0 */
		case 0 :
			r->centre.x ++;						
			/* test de fin de course de la raquette à droite */
			if (r->centre.x > REPERE_SIZE_X-2 - r->largeur/2){
				r->centre.x = REPERE_SIZE_X-2 - r->largeur/2;
			}
		break;
		
		/* à gauche : 1 */
		case 1 :
			r->centre.x --;						
			/* test de fin de course de la raquette à gauche */
			if (r->centre.x < -(REPERE_SIZE_X-2) + r->largeur/2){
				r->centre.x = -(REPERE_SIZE_X-2) + r->largeur/2;
			}
		break;
		
		/* Autre sens */
		default :
			fprintf(stderr, "Fonction mooveRaquette : sens non pris en charge.\n");
			exit(1);
		break;
	
	
	}
}









