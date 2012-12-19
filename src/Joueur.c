#include "Joueur.h"

/* ---- FONCTIONS ---- */

Joueur CreerJoueur(Raquette raquette, int nb_vies){
	Joueur j;
	j.raquette = raquette;
	j.nb_vies = nb_vies;
	j.IMAC.I = 0;
	j.IMAC.M = 0;
	j.IMAC.A = 0;
	j.IMAC.C = 0;
	return j;
}

void dessinVies(Joueur j1, Joueur j2, GLuint texture, Texture t_vie){
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	int i;
	
	/* Vies du joueur 1 */
	for (i=0; i < j1.nb_vies; i++){
		glPushMatrix();
			
			glTranslatef(38, 38 - i*2.7, 0);
			glScalef(2.7, 2.7, 1);
			
			glBegin(GL_QUADS);
				glTexCoord2f(t_vie.coordonnee.x, t_vie.coordonnee.y); glVertex2f(-0.5, 0.5);
				glTexCoord2f(t_vie.coordonnee.x +t_vie.largeur, t_vie.coordonnee.y); glVertex2f(0.5, 0.5);
				glTexCoord2f(t_vie.coordonnee.x + t_vie.largeur, t_vie.coordonnee.y + t_vie.hauteur); glVertex2f(0.5, -0.5);
				glTexCoord2f(t_vie.coordonnee.x , t_vie.coordonnee.y + t_vie.hauteur); glVertex2f(-0.5, -0.5);
			glEnd();
		
		glPopMatrix();
	}

	for (i=0; i<j2.nb_vies; i++){
		glPushMatrix();
			
			glTranslatef(38, -38 + i*2.7, 0);
			glScalef(2.7, 2.7, 3);
			
			glBegin(GL_QUADS);
				glTexCoord2f(t_vie.coordonnee.x, t_vie.coordonnee.y); glVertex2f(-0.5, 0.5);
				glTexCoord2f(t_vie.coordonnee.x +t_vie.largeur, t_vie.coordonnee.y); glVertex2f(0.5, 0.5);
				glTexCoord2f(t_vie.coordonnee.x + t_vie.largeur, t_vie.coordonnee.y + t_vie.hauteur); glVertex2f(0.5, -0.5);
				glTexCoord2f(t_vie.coordonnee.x , t_vie.coordonnee.y + t_vie.hauteur); glVertex2f(-0.5, -0.5);
			glEnd();
		
		glPopMatrix();
	}
}
