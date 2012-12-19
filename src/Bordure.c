#include "Bordure.h"

/* Fonctions */

Bordure CreerBordure(float abscisse, Texture texture){
	Bordure b;
	b.abscisse = abscisse;
	b.texture = texture;
	return b;
}

void dessinBordure(Bordure b, float hauteur_fenetre, GLuint texture){
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glPushMatrix();
	
		glScalef(1, 2*hauteur_fenetre, 1);
		glTranslatef(b.abscisse,0,0);
	
		glBegin(GL_QUADS);
			glTexCoord2f(b.texture.coordonnee.x, b.texture.coordonnee.y); glVertex2f(-0.5, 0.5);
			glTexCoord2f(b.texture.coordonnee.x + b.texture.largeur, b.texture.coordonnee.y); glVertex2f(0.5, 0.5);
			glTexCoord2f(b.texture.coordonnee.x + b.texture.largeur, b.texture.coordonnee.y + b.texture.hauteur); glVertex2f(0.5, -0.5);
			glTexCoord2f(b.texture.coordonnee.x , b.texture.coordonnee.y + b.texture.hauteur); glVertex2f(-0.5, -0.5);
		glEnd();
	
	glPopMatrix();
}
