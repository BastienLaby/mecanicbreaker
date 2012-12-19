#include "Bonus.h"

int cpt_bonus = 0;

Bonus CreerBonus(Point centre, Vecteur direction, float largeur, float hauteur, TypeBonus typeBonus){
	Bonus b;
	b.centre = centre;
	b.direction = direction;
	b.largeur = largeur;
	b.hauteur = hauteur;
	b.typeBonus = typeBonus;
	b.id_bonus = cpt_bonus +1;
	cpt_bonus ++;
	return b;
}

void dessinBonusImac(Joueur* j1, Joueur* j2, GLuint texture){
	int k;
	/* On met à jour les textures */
	/* Joueur 1 */
	if(0 == j1->IMAC.I){
		k = 4;
	}else{
		k = 0;
	}
	j1->IMAC.texI = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	if(0 == j1->IMAC.M){
		k = 5;
	}else{
		k = 1;
	}
	j1->IMAC.texM = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	if(0 == j1->IMAC.A){
		k = 6;
	}else{
		k = 2;
	}
	j1->IMAC.texA = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	if(0 == j1->IMAC.C){
		k = 7;
	}else{
		k = 3;
	}
	j1->IMAC.texC = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	
	/* Joueur 2 */
	if(0 == j2->IMAC.I){
		k = 4;
	}else{
		k = 0;
	}
	j2->IMAC.texI = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	if(0 == j2->IMAC.M){
		k = 5;
	}else{
		k = 1;
	}
	j2->IMAC.texM = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	if(0 == j2->IMAC.A){
		k = 6;
	}else{
		k = 2;
	}
	j2->IMAC.texA = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);
	if(0 == j2->IMAC.C){
		k = 7;
	}else{
		k = 3;
	}
	j2->IMAC.texC = CreerTexture(1, CreerPoint(0, k*0.035), 0.08, 0.035);



	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	/* Bonus du joueur 1 */
	
	/* I */
	glPushMatrix();
		glTranslatef(-38, 38, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j1->IMAC.texI.coordonnee.x, j1->IMAC.texI.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j1->IMAC.texI.coordonnee.x +j1->IMAC.texI.largeur, j1->IMAC.texI.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j1->IMAC.texI.coordonnee.x + j1->IMAC.texI.largeur, j1->IMAC.texI.coordonnee.y + j1->IMAC.texI.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j1->IMAC.texI.coordonnee.x , j1->IMAC.texI.coordonnee.y + j1->IMAC.texI.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* M */
	glPushMatrix();
		glTranslatef(-38, 35.5, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j1->IMAC.texM.coordonnee.x, j1->IMAC.texM.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j1->IMAC.texM.coordonnee.x +j1->IMAC.texM.largeur, j1->IMAC.texM.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j1->IMAC.texM.coordonnee.x + j1->IMAC.texM.largeur, j1->IMAC.texM.coordonnee.y + j1->IMAC.texM.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j1->IMAC.texM.coordonnee.x , j1->IMAC.texM.coordonnee.y + j1->IMAC.texM.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* A */
	glPushMatrix();
		glTranslatef(-38, 33, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j1->IMAC.texA.coordonnee.x, j1->IMAC.texA.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j1->IMAC.texA.coordonnee.x +j1->IMAC.texA.largeur, j1->IMAC.texA.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j1->IMAC.texA.coordonnee.x + j1->IMAC.texA.largeur, j1->IMAC.texA.coordonnee.y + j1->IMAC.texA.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j1->IMAC.texA.coordonnee.x , j1->IMAC.texA.coordonnee.y + j1->IMAC.texA.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* C */
	glPushMatrix();
		glTranslatef(-38, 30.5, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j1->IMAC.texC.coordonnee.x, j1->IMAC.texC.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j1->IMAC.texC.coordonnee.x +j1->IMAC.texC.largeur, j1->IMAC.texC.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j1->IMAC.texC.coordonnee.x + j1->IMAC.texC.largeur, j1->IMAC.texC.coordonnee.y + j1->IMAC.texC.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j1->IMAC.texC.coordonnee.x , j1->IMAC.texC.coordonnee.y + j1->IMAC.texC.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* Bonus du joueur 2 */
	
	/* I */
	glPushMatrix();
		glTranslatef(-38, -30.5, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j2->IMAC.texI.coordonnee.x, j2->IMAC.texI.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j2->IMAC.texI.coordonnee.x +j2->IMAC.texI.largeur, j2->IMAC.texI.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j2->IMAC.texI.coordonnee.x + j2->IMAC.texI.largeur, j2->IMAC.texI.coordonnee.y + j2->IMAC.texI.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j2->IMAC.texI.coordonnee.x , j2->IMAC.texI.coordonnee.y + j2->IMAC.texI.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* M */
	glPushMatrix();
		glTranslatef(-38, -33, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j2->IMAC.texM.coordonnee.x, j2->IMAC.texM.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j2->IMAC.texM.coordonnee.x +j2->IMAC.texM.largeur, j2->IMAC.texM.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j2->IMAC.texM.coordonnee.x + j2->IMAC.texM.largeur, j2->IMAC.texM.coordonnee.y + j2->IMAC.texM.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j2->IMAC.texM.coordonnee.x , j2->IMAC.texM.coordonnee.y + j2->IMAC.texM.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* A */
	glPushMatrix();
		glTranslatef(-38, -35.5, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j2->IMAC.texA.coordonnee.x, j2->IMAC.texA.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j2->IMAC.texA.coordonnee.x +j2->IMAC.texA.largeur, j2->IMAC.texA.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j2->IMAC.texA.coordonnee.x + j2->IMAC.texA.largeur, j2->IMAC.texA.coordonnee.y + j2->IMAC.texA.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j2->IMAC.texA.coordonnee.x , j2->IMAC.texA.coordonnee.y + j2->IMAC.texA.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();
	
	/* C */
	glPushMatrix();
		glTranslatef(-38, -38, 0);
		
		glBegin(GL_QUADS);
			glTexCoord2f(j2->IMAC.texC.coordonnee.x, j2->IMAC.texC.coordonnee.y); glVertex2f(-2,1);
			glTexCoord2f(j2->IMAC.texC.coordonnee.x +j2->IMAC.texC.largeur, j2->IMAC.texC.coordonnee.y); glVertex2f(2, 1);
			glTexCoord2f(j2->IMAC.texC.coordonnee.x + j2->IMAC.texC.largeur, j2->IMAC.texC.coordonnee.y + j2->IMAC.texC.hauteur); glVertex2f(2, -1);
			glTexCoord2f(j2->IMAC.texC.coordonnee.x , j2->IMAC.texC.coordonnee.y + j2->IMAC.texC.hauteur); glVertex2f(-2, -1);
		glEnd();
		
	glPopMatrix();

}


float signe(float nb){
	if(nb>0){ return 1;}
	if(nb<0){ return -1;}
	return 0;
}
