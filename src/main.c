#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "Couleur.h"
#include "Point.h"
#include "Vecteur.h"
#include "Bonus.h"
#include "Brique.h"
#include "Bordure.h"
#include "Joueur.h"
#include "Raquette.h"
#include "Collision.h"
#include "Texture.h"
#include "Niveau.h"

/* Le repere va de -40 à 40 en x, pareil en y */
#define REPERE_SIZE_X 40
#define REPERE_SIZE_Y 40

/* ---------------------------------------------------------------- */
/* --------------- VARIABLES GLOBALES ET STRUCTURES --------------- */
/* --------------------------------------------------------------- */
	
	/* Dimensions de la fenêtre */
	static unsigned int WINDOW_WIDTH = 700;
	static unsigned int WINDOW_HEIGHT = 700;

	/* Nombre de bits par pixel de la fenêtre */
	static const unsigned int BIT_PER_PIXEL = 32;

	/* Nombre minimal de millisecondes separant le rendu de deux images */
	static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

	


/* --------------------------------------------------------------- */
/* -------------------------- FONCTIONS -------------------------- */
/* --------------------------------------------------------------- */

int rand_a_b(int a, int b){
	return rand()%(b-a) +a;
}

/* --------------------------------------------------------------- */
/* ----------------------------- MAIN ---------------------------- */
/* --------------------------------------------------------------- */

int main(int argc, char** argv) {

	/* Initialisation de la SDL */
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	/* Ouverture d'une fenêtre et création d'un contexte OpenGL */
	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	/* Titre de la fenêtre */
	SDL_WM_SetCaption("Mecanic Breaker", NULL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* le repère virtuel */
	gluOrtho2D(-REPERE_SIZE_X, REPERE_SIZE_X, -REPERE_SIZE_Y, REPERE_SIZE_Y);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		
	
	/* Gestion du son avec SDL_MIXER */
	
	/* Initialisation de l'API mixer */
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
	   printf("%s", Mix_GetError());
	}
	
	/* Musique originale */
	Mix_Music* musiquetheme1 = Mix_LoadMUS("sounds/birdpriest.mp3");
	if(musiquetheme1 == NULL){
		fprintf(stderr, "Le chargement de la musique a échouer\n");
		exit(1);
	}
	
	Mix_Music* musiquetheme2 = Mix_LoadMUS("sounds/belinda.mp3");
	if(musiquetheme2 == NULL){
		fprintf(stderr, "Le chargement de la musique a échouer\n");
		exit(1);
	}
	
	Mix_Music* musiqueCourante = musiquetheme2;
	
	/* Sons courts */
	Mix_AllocateChannels(10);
	
	Mix_Chunk* clic = Mix_LoadWAV("sounds/clic.wav");
	if(clic == NULL){
		fprintf(stderr, "Le chargement du son \"clic.wav\" a échouer\n");
		exit(1);
	}
	
	Mix_Chunk* perte_vie = Mix_LoadWAV("sounds/perte de vie.wav");
	if(perte_vie == NULL){
		fprintf(stderr, "Le chargement du son \"perte de vie\" a échouer\n");
		exit(1);
	}
	
	Mix_Chunk* imac = Mix_LoadWAV("sounds/imac.wav");
	if(imac == NULL){
		fprintf(stderr, "Le chargement du son \"imac.wav\" a échouer\n");
		exit(1);
	}
	
	/*Mix_Chunk* lettre = Mix_LoadWAV("sounds/lettre.wav");
	if(lettre == NULL){
		fprintf(stderr, "Le chargement du son \"lettre.wav\" a échouer\n");
		exit(1);
	}*/
	
	Mix_PlayMusic(musiqueCourante, -1);	
	
	/* Variables d'ecran */
	int ecranMenu = 1;
	int ecranJeu = 0;
	int ecranScores = 0;
	int switchLevel = 0;
	int echap = 0;
		
	/* Variables raquettes */
	int r1_MooveRight = 0;
	int r1_MooveLeft = 0;
	int r2_MooveRight = 0;
	int r2_MooveLeft = 0;
	
	int k,i;
	int loop = 1;
	int mv = 0;
	int passerNiveauSuivant = 0;
	int niveauActuel = 2;
	int reboot = 0;
	
	/* Creation du niveau */
	
	/* Chargement des tilesets */
	GLuint* texture1 = chargementImagesTheme1();
	GLuint* texture2 = chargementImagesTheme2();
	
	GLuint* current_texture = texture2;
	
	/* Création des joueurs et des raquettes */
	Joueur joueur1 = CreerJoueur(CreerRaquette(CreerPoint(0, 37.5), 10, 1.5, CreerTexture(1, CreerPoint(0.09,0), 0.07, 0.56), CreerTexture(1, CreerPoint(0.095,0.565), 0.115, 0.115)), 3);
	Joueur joueur2 = CreerJoueur(CreerRaquette(CreerPoint(0, -37.5), 10, 1.5, CreerTexture(1, CreerPoint(0.09,0), 0.07, 0.555), CreerTexture(1, CreerPoint(0.21,0.56), 0.12, 0.12)), 3);
	
	Niveau niveau = CreerNiveau(niveauActuel, &joueur1, &joueur2);
	
	/* Création des bordures */
	Bordure bordure_gauche = CreerBordure(-38, CreerTexture(1, CreerPoint(0.08,0), 0.01, 1));
	Bordure bordure_droite = CreerBordure(38, CreerTexture(1, CreerPoint(0.08,0), 0.01, 1));

	/* Création de la texture vie */
	Texture t_vie = CreerTexture(1, CreerPoint(0.165, 0.14), 0.14, 0.13);

	/* variables de jeu */
	float alpha = 0.1;
	float xnumber, ynumber, x_souris, y_souris, xpos, ypos, xson, yson;
	float incrementAngleEngrenages = 0.5;
	int current_theme = 1;
	float volume = 0;
	int mouse_is_down = 0;
	float xcurseurmusic = 0;
	int souris_actuelle = 0;
	int tps_fin_niveau = 60*1;
	int niveau_max = 5;

	/* -------------------------------------------------------------------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------- LISTES D'AFFICHAGE ------------------------------------------------------------- */
	
	GLuint l_dessinFond;
	GLuint l_dessinMenu;
		
	l_dessinFond = glGenLists(1);
	
	if(l_dessinFond == 0){
		fprintf(stderr, "Erreur lors du parametrage de la liste de dessin du fond\n");
		exit(1);
	}
	
	l_dessinMenu = glGenLists(6);
	for(i=0; i<4; i++){
		if(l_dessinMenu+i == 0){
			fprintf(stderr, "Erreur lors du parametrage de la liste de dessin du menu\n");
		}
	}
	
	/* LE FOND */
	glNewList(l_dessinFond,GL_COMPILE);
		
		glPushMatrix();
			glScalef(80,80,1);			
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);glVertex2f(-0.5,0.5);
				glTexCoord2f(1, 0); glVertex2f(0.5,0.5);
				glTexCoord2f(1, 1); glVertex2f(0.5,-0.5);
				glTexCoord2f(0, 1); glVertex2f(-0.5,-0.5);
			glEnd();
		glPopMatrix();
	glEndList();
	
	/* LE TITRE */
	glNewList(l_dessinMenu,GL_COMPILE);
			glPushMatrix();
				glTranslatef(-25, -25,0);
				glScalef(25,16.5,1);				
				glBegin(GL_QUADS);
					glTexCoord2f(0.09, 0.73); glVertex2f(-0.5, 0.5);
					glTexCoord2f(0.5, 0.73); glVertex2f(0.5, 0.5);
					glTexCoord2f(0.5, 1); glVertex2f(0.5, -0.5);
					glTexCoord2f(0.09, 1); glVertex2f(-0.5, -0.5);
				glEnd();
			glPopMatrix();
	glEndList();
	
	/* ROUE DU MILIEU */
	glNewList(l_dessinMenu+1,GL_COMPILE);

			glPushMatrix();
				glScalef(35,35,1);				
				glBegin(GL_QUADS);
					glTexCoord2f(0.55, 0); glVertex2f(-0.5, 0.5);
					glTexCoord2f(0.86, 0); glVertex2f(0.5, 0.5);
					glTexCoord2f(0.86, 0.56); glVertex2f(0.5, -0.5);
					glTexCoord2f(0.55, 0.56); glVertex2f(-0.5, -0.5);
				glEnd();
			
			glPopMatrix();
	glEndList();
	
	/* GROSSE ROUE EN HAUT A GAUCHE */
	glNewList(l_dessinMenu+2,GL_COMPILE);

			glPushMatrix();				
				glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex2f(-0.5, 0.5);
					glTexCoord2f(0.55, 0); glVertex2f(0.5, 0.5);
					glTexCoord2f(0.55, 1); glVertex2f(0.5, -0.5);
					glTexCoord2f(0, 1); glVertex2f(-0.5, -0.5);
				glEnd();
			
			glPopMatrix();
	glEndList();
	
	/* BOUTON QUITTER */
	glNewList(l_dessinMenu+3,GL_COMPILE);

			glPushMatrix();		
				glTranslatef(22,-24,0);
				glScalef(15,5.25,1);		
				glBegin(GL_QUADS);
					glTexCoord2f(0.16, 0.27); glVertex2f(-0.5, 0.5);
					glTexCoord2f(0.36, 0.27); glVertex2f(0.5, 0.5);
					glTexCoord2f(0.36, 0.34); glVertex2f(0.5, -0.5);
					glTexCoord2f(0.16, 0.34); glVertex2f(-0.5, -0.5);
				glEnd();
			
			glPopMatrix();
	glEndList();
	
	/* BOUTON JOUER */
	glNewList(l_dessinMenu+4,GL_COMPILE);

			glPushMatrix();
				glTranslatef(22,-18,0);
				glScalef(15,5.25,1);				
				glBegin(GL_QUADS);
					glTexCoord2f(0.16, 0.34); glVertex2f(-0.5, 0.5);
					glTexCoord2f(0.36, 0.34); glVertex2f(0.5, 0.5);
					glTexCoord2f(0.36, 0.41); glVertex2f(0.5, -0.5);
					glTexCoord2f(0.16, 0.41); glVertex2f(-0.5, -0.5);
				glEnd();
			glPopMatrix();

	glEndList();
	
	/* BOUTON THEME */
	glNewList(l_dessinMenu+5,GL_COMPILE);

			glPushMatrix();	
				glTranslatef(22,-30,0);
				glScalef(15,5.25,1);			
				glBegin(GL_QUADS);
					glTexCoord2f(0.16, 0.41); glVertex2f(-0.5, 0.5);
					glTexCoord2f(0.36, 0.41); glVertex2f(0.5, 0.5);
					glTexCoord2f(0.36, 0.47); glVertex2f(0.5, -0.5);
					glTexCoord2f(0.16, 0.47); glVertex2f(-0.5, -0.5);
				glEnd();
			
			glPopMatrix();
	glEndList();
	
	while(loop) {
		
		
		
		/* Récupération du temps au début de la boucle */
		Uint32 startTime = SDL_GetTicks();
		
		/* A décommenter si double buffering */
		glClear(GL_COLOR_BUFFER_BIT);
		
		/* On cache la souris */
		SDL_ShowCursor(0);
		glColor3ub(255,255,255);
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		
		/* Dessin du fond */
		glBindTexture(GL_TEXTURE_2D, current_texture[0]);
			glCallList(l_dessinFond);
		glBindTexture(GL_TEXTURE_2D, 0);

		/* ------------------------ GESTION DES ECRANS ------------------------ */
		/* -------------------------------------------------------------------- */			
	
		if(!echap){
		
			if(ecranMenu){
	
				/* Dessin du titre */
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, current_texture[1]);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
					glCallList(l_dessinMenu);
				glBindTexture(GL_TEXTURE_2D, 0);
		
				/* Dessin de la roue du milieu */
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, current_texture[2]);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
				glPushMatrix();
					glRotatef(alpha, 0, 0, 1);
					glCallList(l_dessinMenu+1);
				glPopMatrix();
		
				glBindTexture(GL_TEXTURE_2D, 0);
					
				/* Dessin de la roue du haut */
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, current_texture[2]);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
				glPushMatrix();
					glTranslatef(-40, 40, 0);
					glScalef(78, 78,1);
					glRotatef(-alpha, 0, 0, 1);
					glCallList(l_dessinMenu+2);
				glPopMatrix();
		
				glBindTexture(GL_TEXTURE_2D, 0);
		
				alpha = alpha + incrementAngleEngrenages;
		
				/* Dessin des boutons */
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, current_texture[1]);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
				glCallList(l_dessinMenu+3);
				glCallList(l_dessinMenu+4);
				glCallList(l_dessinMenu+5);
		
				glBindTexture(GL_TEXTURE_2D, 0);
			}
	
			if(ecranJeu){
		
				/* Si on a relancé le jeu */
				if(reboot){
					/* On réinitialise tout */
					niveau.joueur1->nb_vies = 3;
					niveau.joueur2->nb_vies = 3;
					niveau.joueur1->IMAC.I = 0;
					niveau.joueur1->IMAC.M = 0;
					niveau.joueur1->IMAC.A = 0;
					niveau.joueur1->IMAC.C = 0;
					niveau.joueur2->IMAC.I = 0;
					niveau.joueur2->IMAC.M = 0;
					niveau.joueur2->IMAC.A = 0;
					niveau.joueur2->IMAC.C = 0;
			
					niveau.joueur1->raquette.centre.x = 0;
					niveau.joueur1->raquette.centre.y = 38;
					niveau.joueur2->raquette.centre.x = 0;
					niveau.joueur2->raquette.centre.y = -38;
			
					niveau.joueur1->raquette.largeur = 10;
					niveau.joueur2->raquette.largeur = 10;
			
					niveauActuel = 1;
					tps_fin_niveau = 1*60;
			
					switchLevel = 1;
					mv = -60;
			
					libererListeBalle(niveau.balles);
					free(niveau.briques);
			
					/* On créé un nouveau niveau */				
					niveau = CreerNiveau(niveauActuel, niveau.joueur1, niveau.joueur2);
			
					reboot = 0;
			
					Mix_PlayMusic(musiqueCourante, 1); 
			
				}
		
				if(switchLevel){
		
					/* Animation du changement de niveau */				
			
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glBindTexture(GL_TEXTURE_2D, current_texture[1]);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
					glPushMatrix();
						glTranslatef(-60 + mv, 0, 0);
						glScalef(20, 20, 0);
				
						/* Calcul des coordonnees sur le tileset */
						xnumber = 0.5 + ((niveauActuel-1)%3)*0.14;
						ynumber = 0 + ((niveauActuel-1)/3)*0.26; 
				
						/* dessin */
						glBegin(GL_QUADS);
							glTexCoord2f(xnumber, ynumber); glVertex2f(-0.5, 1);
							glTexCoord2f(xnumber + 0.14, ynumber); glVertex2f(0.5, 1);
							glTexCoord2f(xnumber + 0.14, ynumber + 0.26); glVertex2f(0.5, -1);
							glTexCoord2f(xnumber, 0 + ynumber + 0.26); glVertex2f(-0.5, -1);
						glEnd();
				
					glPopMatrix();
			
					mv += 1;
					if(mv >120){
						switchLevel = 0;
						alpha = 0;
					}
			
		
				}else{
		
							
		
					/* ------------------------ CODE DE DESSIN  --------------------------- */
					/* -------------------------------------------------------------------- */

					/* DESSIN DES BORDS */
					dessinBordure(bordure_gauche, REPERE_SIZE_X, current_texture[1]);
					dessinBordure(bordure_droite, REPERE_SIZE_X, current_texture[1]);
		
					/* DESSIN DES BRIQUES */

					for(i=0; i<niveau.nb_briques; i++){
						/* Si la brique n'est pas cassée, on la dessine */
						if(niveau.briques[i].solidite > 0){
							dessinBrique(niveau.briques[i], current_texture[1]);
						}					
						/* On incrémente le compteur */
						k++;				
					}

					/* RAQUETTES DES RAQUETTES */
					dessinRaquette(niveau.joueur1->raquette, 0, current_texture[1], alpha);
					dessinRaquette(niveau.joueur2->raquette, 1, current_texture[1], alpha);
					alpha = alpha + 0.5;
					if(alpha > 360){ alpha = 0; }
	
					/* DESSIN DES BONUS IMAC */
					dessinBonusImac(niveau.joueur1, niveau.joueur2, current_texture[1]);
	
					/* GESTION ET DESSIN DES VIES */
			
					if(niveau.joueur1->IMAC.I && niveau.joueur1->IMAC.M && niveau.joueur1->IMAC.A && niveau.joueur1->IMAC.C){
						niveau.joueur1->nb_vies += 3;
						Mix_PlayChannel(-1, imac, 1);
						niveau.joueur1->IMAC.I = 0;
						niveau.joueur1->IMAC.M = 0;
						niveau.joueur1->IMAC.A = 0;
						niveau.joueur1->IMAC.C = 0;
					}
			
					if(niveau.joueur2->IMAC.I && niveau.joueur2->IMAC.M && niveau.joueur2->IMAC.A && niveau.joueur2->IMAC.C){
						niveau.joueur2->nb_vies += 3;
						Mix_PlayChannel(-1, imac, 1);
						niveau.joueur2->IMAC.I = 0;
						niveau.joueur2->IMAC.M = 0;
						niveau.joueur2->IMAC.A = 0;
						niveau.joueur2->IMAC.C = 0;
					}
			
					/* Si un joueur n'a plus de points de vie, il a perdu */
					if(0 == niveau.joueur1->nb_vies){
						ecranJeu = 0;
						ecranScores = 1;
						Mix_PauseMusic();
						Mix_PlayChannel(-1, perte_vie, 1);
					}
			
					if(0 == niveau.joueur2->nb_vies){
						ecranJeu = 0;
						ecranScores = 1;
						Mix_PauseMusic();
						Mix_PlayChannel(-1, perte_vie, 1);
					}
			
			
					dessinVies(*niveau.joueur1, *niveau.joueur2, current_texture[1], t_vie);

					/* DESSIN & DEPLACEMENT RAQUETTE */

						/* Raquette du joueur du haut */		
						if(r1_MooveRight){
							deplacerRaquette(&niveau.joueur1->raquette, 0);
						}

						if(r1_MooveLeft){
							deplacerRaquette(&niveau.joueur1->raquette, 1);
						}
	
						/* Raquette du joueur du bas */
						if(r2_MooveRight){
							deplacerRaquette(&niveau.joueur2->raquette, 0);
						}

						if(r2_MooveLeft){
							deplacerRaquette(&niveau.joueur2->raquette, 1);
						}
	
						/* attraperBonus(listeBonus, &joueur1, &joueur2); */
	
					/* DESSIN DES BALLES */
					dessinBalles(niveau.balles, current_texture[1]);
	
					/* --------------------- Fin du code de dessin -------------------- */
					/* ---------------------------------------------------------------- */

					/* ------------------------ Gestion des déplacements et des collisions ------------------------ */
					/* -------------------------------------------------------------------------------------------- */		


					/* DEPLACEMENT DES BALLES */			
					deplacerBalles(niveau.balles, niveau.joueur1, niveau.joueur2);

					/* Gestion des deux balles principales */
					if(niveau.mb1->balle.etat==PERDUE){
						/* On repositionne la balle sur la raquette */
						niveau.mb1->balle.centre.x = niveau.joueur1->raquette.centre.x;
						niveau.mb1->balle.centre.y = niveau.joueur1->raquette.centre.y - niveau.joueur1->raquette.hauteur/2 - niveau.mb1->balle.rayon;
						niveau.mb1->balle.direction = CreerVecteur(0,-0.6);
						niveau.mb1->balle.etat=SUR_RAQUETTE;
					}
			
					if(niveau.mb1->balle.etat==SUR_RAQUETTE){
						/* On repositionne la balle sur la raquette */
						niveau.mb1->balle.centre.x = niveau.joueur1->raquette.centre.x;
						niveau.mb1->balle.centre.y = niveau.joueur1->raquette.centre.y - niveau.joueur1->raquette.hauteur/2 - niveau.mb1->balle.rayon;
					}

					if(niveau.mb2->balle.etat==PERDUE){
						/* On repositionne la balle sur la raquette */
						niveau.mb2->balle.centre.x = niveau.joueur2->raquette.centre.x;
						niveau.mb2->balle.centre.y = niveau.joueur2->raquette.centre.y + niveau.joueur2->raquette.hauteur/2 + niveau.mb2->balle.rayon;
						niveau.mb2->balle.direction = CreerVecteur(0, 0.6);
						niveau.mb2->balle.etat=SUR_RAQUETTE;
					}
			
					if(niveau.mb2->balle.etat==SUR_RAQUETTE){
						/* On repositionne la balle sur la raquette */
						niveau.mb2->balle.centre.x = niveau.joueur2->raquette.centre.x;
						niveau.mb2->balle.centre.y = niveau.joueur2->raquette.centre.y + niveau.joueur2->raquette.hauteur/2 + niveau.mb2->balle.rayon;
					}
	
					/* Collision avec les bordures */			
					collisionBallesBordures(niveau.balles, bordure_gauche, bordure_droite);

					/* Collision avec les raquettes */			
					collisionBallesRaquettes(niveau.balles, niveau.joueur1, niveau.joueur2);


					passerNiveauSuivant = 1;
					/* Collision avec les briques */			
					for(i=0; i<niveau.nb_briques; i++){

						/* Si la brique n'est pas cassée */				
						if(niveau.briques[i].solidite > 0){
							passerNiveauSuivant = 0;						
							/* Si une des balles colllisionne cette brique */
							if(collisionBallesBrique(niveau.balles, &niveau.briques[i])){
								niveau.briques[i].couleur = multCouleurC(CreerCouleur(255,255,255), (float)0.2*niveau.briques[i].solidite);
							}
						}	
					}
					
					if(passerNiveauSuivant){
						printf("%d\n", tps_fin_niveau);
						tps_fin_niveau --;
						if(tps_fin_niveau > 0){
							passerNiveauSuivant = 0;
						}
					}
			
					/* Gestion des niveau */
			
					/* S'il n'y a plus de briques sur le niveau */
					if(passerNiveauSuivant){glBindTexture(GL_TEXTURE_2D, 0);
						
						niveauActuel += 1;
						
						/* libere toutes les ressources du niveau */
						libererListeBalle(niveau.balles);
						free(niveau.briques);
						
						/* Si il n'y a plus de niveaux */
						if(niveauActuel>niveau_max){
							ecranScores = 1;
							ecranJeu = 0;
							Mix_PauseMusic();
						}else{
							switchLevel = 1;
							mv = -60;
							/* On créé un nouveau niveau */				
							niveau = CreerNiveau(niveauActuel, niveau.joueur1, niveau.joueur2);
						}				
					}
			
					/* ------------------- Fin de la gestion des déplacements et des collision -------------------- */
					/* -------------------------------------------------------------------------------------------- */
				}
			}
	
	
	
			if(ecranScores){
	
				if(niveau.joueur2->nb_vies != niveau.joueur1->nb_vies){
				
					/* Si le joueur 1 a gagné */
					if(niveau.joueur2->nb_vies == 0){
						/* On dessine le joueur 1 en gros */
						niveau.joueur1->raquette.centre.x = 0;
						niveau.joueur1->raquette.centre.y = 0;
						glPushMatrix();
							glScalef(3,3,1);
							dessinRaquette(niveau.joueur1->raquette, 0, current_texture[1], alpha);
						glPopMatrix();
						alpha = alpha + 0.5;
					}
		
					/* Si le joueur 2 a gagné */
					if(niveau.joueur1->nb_vies == 0){
						/* On dessine le joueur 2 en gros */
						niveau.joueur2->raquette.centre.x = 0;
						niveau.joueur2->raquette.centre.y = 0;
						glPushMatrix();
							glScalef(3,3,1);
							dessinRaquette(niveau.joueur2->raquette, 0, current_texture[1], alpha);
						glPopMatrix();
						alpha = alpha + 0.5;
					}
		
					for(i=0; i<10; i++){
		
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glBindTexture(GL_TEXTURE_2D, current_texture[1]);
						glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
						glPushMatrix();					
				
							glRotatef(-alpha + i*36, 0, 0, 1);
							glTranslatef(25, 0, 0);
		
							/* On dessine les balles */		
							glBegin(GL_QUADS);		
								glTexCoord2f(niveau.balles->balle.texture.coordonnee.x, niveau.balles->balle.texture.coordonnee.y);
									glVertex2f(-1,1);
								glTexCoord2f(niveau.balles->balle.texture.coordonnee.x + niveau.balles->balle.texture.largeur, niveau.balles->balle.texture.coordonnee.y);
									glVertex2f(1,1);
								glTexCoord2f(niveau.balles->balle.texture.coordonnee.x + niveau.balles->balle.texture.largeur, niveau.balles->balle.texture.coordonnee.y + niveau.balles->balle.texture.hauteur);
									glVertex2f(1,-1);
								glTexCoord2f(niveau.balles->balle.texture.coordonnee.x, niveau.balles->balle.texture.coordonnee.y + niveau.balles->balle.texture.hauteur);
									glVertex2f(-1, -1);
							glEnd();
							glColor3ub(255,255,255);
						glPopMatrix();
						
						glBindTexture(GL_TEXTURE_2D, 0);
					
					}
				}else{
				
					
				
					/* On dessine le joueur 1 en petit */
					niveau.joueur1->raquette.centre.x = -10;
					niveau.joueur1->raquette.centre.y = 0;
					glPushMatrix();
						glScalef(1.5,1.5,1);
						dessinRaquette(niveau.joueur1->raquette, 0, current_texture[1], alpha);
					glPopMatrix();
				
				
					/* On dessine le joueur 2 en petit */
					niveau.joueur2->raquette.centre.x = 10;
					niveau.joueur2->raquette.centre.y = 0;
					glPushMatrix();
						glScalef(1.5,1.5,1);
						dessinRaquette(niveau.joueur2->raquette, 0, current_texture[1], alpha);
					glPopMatrix();
				
					alpha = alpha + 0.5;
				
				}
				
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, current_texture[1]);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
				glCallList(l_dessinMenu+3);
				glCallList(l_dessinMenu+4);
				
				glBindTexture(GL_TEXTURE_2D, 0);	
	
			}
			
		}else{
		
			/* Affichage du fond */
			glBindTexture(GL_TEXTURE_2D, current_texture[3]);
			glPushMatrix();
				glScalef(80,80,1);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(-0.5,0.5);
					glTexCoord2f(1,0); glVertex2f(0.5,0.5);
					glTexCoord2f(1,1); glVertex2f(0.5,-0.5);
					glTexCoord2f(0,1); glVertex2f(-0.5,-0.5);
		
				glEnd();
			glPopMatrix();
			
			glBindTexture(GL_TEXTURE_2D, 0);
			
			/* Affichage des icones de son */
			xson = 0.79;
			yson = 0.82;
			
			if(volume < 0.66){
				xson = 0.65;
			}
			
			if(volume == 0){
				xson = 0.51;
			}			
			
			glBindTexture(GL_TEXTURE_2D, current_texture[1]);
			glPushMatrix();
				glTranslatef(-25, 30, 0);
				glScalef(5,5,1);
				glBegin(GL_QUADS);
					glTexCoord2f(xson, yson); glVertex2f(-0.5,0.5);
					glTexCoord2f(xson + 0.125, yson); glVertex2f(0.5,0.5);
					glTexCoord2f(xson + 0.125, yson + 0.15); glVertex2f(0.5,-0.5);
					glTexCoord2f(xson, yson + 0.15); glVertex2f(-0.5,-0.5);
		
				glEnd();
			glPopMatrix();
			
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glBegin(GL_LINES);
				glColor3ub(0,0,0);
					glVertex2f(-22,30);
					glVertex2f(0,30);
				glColor3ub(255,255,255);
			glEnd();
			
			glPushMatrix();
				glTranslatef(xcurseurmusic, 29, 0);
				glScalef(1, 2, 1);
				glBegin(GL_QUADS);
					glColor3ub(51,51,51);
						glVertex2f(-1,1);
						glVertex2f(0,1);
						glVertex2f(0,0);
						glVertex2f(-1,0);
					glColor3ub(255,255,255);
				glEnd();
			glPopMatrix();
		
		}
	
		

		/* AFFICHAGE DE LA SOURIS */
		
		/* Si on est sur un bouton, on choisit le bonne texture */
		souris_actuelle = 0;

		if(x_souris>14.5 && x_souris<29.5 && y_souris <-15.375 && y_souris>-20.625){
			souris_actuelle = 1;
		}
		
		if(x_souris>14.5 && x_souris<29.5 && y_souris <-21.375 && y_souris>-26.625){
			souris_actuelle = 1;
		}
		
		if(ecranMenu && x_souris>14.5 && x_souris<29.5 && y_souris <-27.375 && y_souris>-32.625){
			souris_actuelle = 1;
		}
		
		if(echap && x_souris <= 0 && x_souris >= -22 && y_souris >= 29 && y_souris <= 31){
			souris_actuelle = 1;
		}
		
		
		
		/* on dessine le curseur */
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, current_texture[souris_actuelle + 4]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
		glPushMatrix();
			glTranslatef(x_souris, y_souris, 0);
			glScalef(2, 2, 1);
			
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(-0.5, 0.5);
				glTexCoord2f(1,0); glVertex2f(0.5,0.5);
				glTexCoord2f(1,1); glVertex2f(0.5,-0.5);
				glTexCoord2f(0,1); glVertex2f(-0.5, -0.5);
				
			glEnd();
		glPopMatrix();
		
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		/* Echange du front et du back buffer : mise à jour de la fenêtre */
		SDL_GL_SwapBuffers();
		   
		/* Boucle traitant les evenements */
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
		
			  /* L'utilisateur ferme la fenêtre : */
			  if(e.type == SDL_QUIT) {
				loop = 0;
				break;
			  }
			  
			  /* EVENEMENTS : */
			  switch(e.type) {
				
				
				case SDL_MOUSEMOTION :
				
					/* On récupère les coordonnées de la souris */
					x_souris = (e.motion.x - (float)WINDOW_WIDTH/2)/10;
				  	y_souris = -(e.motion.y - (float)WINDOW_HEIGHT/2)/10;
				  	
				  	/* Si on essaye de modifier le son */
				  	if(echap && mouse_is_down){
				  		
				  		/* Si le curseur est hors de la slide bare, on le borne */
				  		if(x_souris < -22){
				  			x_souris = -22;
				  		}
				  		if(x_souris > 0){
				  			x_souris = 0;
				  		}
				  		
				  		/* On calcule le volume en fonction de la position bornée du curseur */
						volume = (x_souris + 22)/22;
						xcurseurmusic = -(1-volume)*22;
						Mix_VolumeMusic((0 + volume)*MIX_MAX_VOLUME);
				  	}
				
				break;
				
				/* Si on appuie sur une touche */
				case SDL_KEYDOWN :
				
					/* Si on est en jeu */
					if(ecranJeu){
					
						switch (e.key.keysym.sym){
						
							/* fleche droite -> fait bouger la raquette 1 à droite */
							case SDLK_RIGHT :
								r1_MooveRight = 1;						
							break;
					
							/* fleche gauche -> fait bouger la raquette 1 à gauche*/
							case SDLK_LEFT :
								r1_MooveLeft = 1;
							break;
						
							/* touche Z -> fait bouger la raquette 2 à droite */
							case SDLK_z :
								r2_MooveRight = 1;						
							break;
					
							/* touche A -> fait bouger la raquette 2 à gauche*/
							case SDLK_a :
								r2_MooveLeft = 1;
							break;
						
							/* touche SHIFT de droite : lancer la balle du joueur 1 */
							case SDLK_RSHIFT :
								if(niveau.mb1->balle.etat==SUR_RAQUETTE){
									niveau.mb1->balle.etat = EN_JEU;
								}								
							break;
						
							/* touche ALT de gauche : lancer la balle du joueur 1 */
							case SDLK_LSHIFT :
								if(niveau.mb2->balle.etat==SUR_RAQUETTE){
									niveau.mb2->balle.etat = EN_JEU;
								}
							break;
					
							default : break;
						}
					
					}
				
					
				break;
					
				/* Si on relache une touche, les raquettes s'arrêtent */
				case SDL_KEYUP :
				
					switch (e.key.keysym.sym){
						
						/* fleche droite -> la raquette 1 s'arrête*/
						case SDLK_RIGHT :
							r1_MooveRight = 0;						
						break;
					
						/* fleche gauche la raquette 1 s'arrête */
						case SDLK_LEFT :
							r1_MooveLeft = 0;
						break;
						
						/* touche Z -> la raquette 2 s'arrête*/
						case SDLK_z :
							r2_MooveRight = 0;						
						break;
					
						/* touche A -> la raquette 1 s'arrête */
						case SDLK_a :
							r2_MooveLeft = 0;
						break;
						
						case SDLK_ESCAPE :
							if(echap == 0){
								echap = 1;
							}else{
								echap = 0;
							}							
						break;
					
						default : break;
					}
				break;
				
				case SDL_MOUSEBUTTONDOWN :
				
					/* On récupère les coordonnées de la souris */
					x_souris = (e.motion.x - (float)WINDOW_WIDTH/2)/10;
				  	y_souris = -(e.motion.y - (float)WINDOW_HEIGHT/2)/10;
					
					/* Si on clique sur la zone du curseur */
					if(x_souris <= 0 && x_souris >= -22 && y_souris >= 29 && y_souris <= 31){
						mouse_is_down = 1;
					}
					
					
					
									
				break;
				
				case SDL_MOUSEBUTTONUP :
				
					mouse_is_down = 0;
					
					/* Si on est sur le menu et si c'est le bouton gauche*/
					if(ecranMenu && e.button.button == SDL_BUTTON_LEFT){
						
						
						xpos = (e.button.x - (float)WINDOW_WIDTH/2)/10;
					  	ypos = -(e.button.y - (float)WINDOW_HEIGHT/2)/10;
						
						/* Si on a cliqué sur le bouton JOUER */
						if(!ecranScores && xpos>14.5 && xpos<29.5 && ypos <-15.375 && ypos>-20.625){
							Mix_PlayChannel(-1, clic, 1);
							ecranMenu = 0;
							ecranJeu = 1;
							switchLevel = 1;
						}
						
						
						/* Si on a cliqué sur le bouton QUITTER */
						if(xpos>14.5 && xpos<29.5 && ypos <-21.375 && ypos>-26.625){
							Mix_PlayChannel(-1, clic, 1);
							loop = 0;
						}
						
						
						/* Si on a cliqué sur le bouton THEME */
						if(!ecranScores && xpos>14.5 && xpos<29.5 && ypos <-27.375 && ypos>-32.625){
							
							/* changement de theme */
							if(current_theme == 0){
								current_theme = 1;
								current_texture = texture2;
							}else{
								current_theme = 0;
								current_texture = texture1;
							}
							
							/* changement de musique */
							if(musiqueCourante == musiquetheme1){
								musiqueCourante = musiquetheme2;
							}else{
								musiqueCourante = musiquetheme1;
							}
							
							Mix_PauseMusic();
							Mix_PlayMusic(musiqueCourante, 1); 
							
							
						}
					}
					
					/* Si on est sur l'ecran score et si c'est le bouton gauche*/
					if(ecranScores && e.button.button == SDL_BUTTON_LEFT){
						
						xpos = (e.button.x - (float)WINDOW_WIDTH/2)/10;
					  	ypos = -(e.button.y - (float)WINDOW_HEIGHT/2)/10;
						
						/* Si on a cliqué sur le bouton JOUER */
						if(xpos>14.5 && xpos<29.5 && ypos <-15.375 && ypos>-20.625){
							Mix_PlayChannel(-1, clic, 1);
							reboot = 1;
							ecranJeu = 1;
							ecranScores = 0;
							switchLevel = 1;
							niveauActuel = 1;
						}
						
						/* Si on a cliqué sur le bouton QUITTER */
						if(xpos>14.5 && xpos<29.5 && ypos <-21.375 && ypos>-26.625){
							Mix_PlayChannel(-1, clic, 1);
							loop = 0;
						}
						
					}
				break;
						
				default :
				break;
				
			  } /* FIN SWITCH EVENT*/
		} /* FIN BOUCLE */

		/* Calcul du temps écoulé */
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		/* Si trop peu de temps s'est écoulé, on met en pause le programme */
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
		  SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	} /* FIN BOUCLE INFINIE*/
  
  	free(niveau.briques);
	libererListeBalle(niveau.balles);
	free(texture1);
	free(texture2);
	
	/* Libération des ressources SDl_MIXER */	
	Mix_CloseAudio();
	Mix_FreeMusic(musiquetheme1);
	Mix_FreeMusic(musiquetheme2);
	Mix_FreeChunk(clic);
	Mix_FreeChunk(perte_vie);
	Mix_FreeChunk(imac);
	/*Mix_FreeChunk(lettre);*/

	
	
	/* Liberation des ressources associées à la SDL */ 
	SDL_Quit();
	return EXIT_SUCCESS;
}






