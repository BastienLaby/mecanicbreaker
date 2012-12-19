#include "Collision.h"

int collisionBallesBordures(MaillonBalle* liste, Bordure bordureG, Bordure bordureD){

	int collision = 0;

	while(liste!=NULL){

		Point positionSuivante = pointPlusVecteur(liste->balle.centre, liste->balle.direction);
	
		/* -------------------------------------------------------------------------------------------------------------------------------------- */
		/* ------- Pour tester la collision entre la balle et la bordure, on va comparer la position de la balle avec sa position suivante ------ */
		/*   Si par exemple la balle est à gauche d'une bordure à un moment t, et qu'elle est à droite au moment t+1, alors il y a collision      */
		/* -------------------------------------------------------------------------------------------------------------------------------------- */
	
		/* Bordure droite (= la balle va de gauche à droite) */
	
		if (liste->balle.direction.x >0 && (liste->balle.centre.x + liste->balle.rayon) <= bordureD.abscisse && (positionSuivante.x + liste->balle.rayon) >= bordureD.abscisse){
			liste->balle.direction.x = - liste->balle.direction.x;
			collision = 1;
		}
	
		/* Bordure gauche (= la balle va de droite à gauche) */
	
		if (liste->balle.direction.x <0 && (liste->balle.centre.x - liste->balle.rayon) >= bordureG.abscisse && (positionSuivante.x - liste->balle.rayon) <= bordureG.abscisse){
			liste->balle.direction.x = - liste->balle.direction.x;
			collision = 1;
		}
		
		liste = liste->next;
	}
	
	return collision;
}

int collisionBallesRaquettes(MaillonBalle* liste, Joueur* joueur1, Joueur* joueur2){

	/* Test de validité des pointeurs */
	if(joueur1 == NULL || joueur2 == NULL){
		printf("Fonction collisionBallesRaquettes : Echec lors du paramétrage des pointeurs.\n");
		exit(1);
	}
	
	/* ----------------------------------------------------------------------------------------------------------------------------------------- */
	/* ------ Pour tester la collision entre la balle et la raquette, on va comparer la position de la balle avec sa position suivante --------- */
	/* Si par exemple la balle est en dehors de la raquette à un moment t, et qu'elle est dans la raquette au moment t+1, alors il y a collision */
	/* ----------------------------------------------------------------------------------------------------------------------------------------- */
	
	int collision = 0;
	
	while(liste!=NULL){	
	
		Point positionSuivante = pointPlusVecteur(liste->balle.centre, liste->balle.direction);
		float vitesse_initiale = norme(liste->balle.direction);
	
	
		/* Si la balle monte */
	
		/* Test en ordonnée */
		if (liste->balle.direction.y>0 
		&& (liste->balle.centre.y + liste->balle.rayon) <= (joueur1->raquette.centre.y - joueur1->raquette.hauteur/2) 
		&& (positionSuivante.y + liste->balle.rayon) >= (joueur1->raquette.centre.y - joueur1->raquette.hauteur/2)){
		
			/* Test en abscisse */
			if (positionSuivante.x >= (joueur1->raquette.centre.x - joueur1->raquette.largeur/2) && positionSuivante.x <= (joueur1->raquette.centre.x + joueur1->raquette.largeur/2)){
			
				/* On teste pour savoir de quel coté de la raquette la balle a rebondi */
				float testRebond = liste->balle.centre.x - joueur1->raquette.centre.x;
			
				/* La nouvelle direction en x de la balle */
				float composante_x = 0.05*(liste->balle.centre.x - joueur1->raquette.centre.x);
			
				/* Si la balle se trouve sur la partie gauche de la raquette */
				if(testRebond < 0){	
					liste->balle.direction.x = composante_x;
					liste->balle.direction.y = - liste->balle.direction.y;
				}
			
				/* Si la balle se trouve sur la partie droite de la raquette */
				if(testRebond > 0){
					liste->balle.direction.x = composante_x;
					liste->balle.direction.y = - liste->balle.direction.y;
				}
			
				/* Si la balle se trouve pile au centre de la raquette, elle rebondit verticalement et perd son facteur directeur en x*/
				if(testRebond == 0){
					liste->balle.direction.x = 0;
					liste->balle.direction.y = - liste->balle.direction.y;
				}
			
				liste->balle.direction = normaliser(liste->balle.direction);
				liste->balle.direction = multVecteur(liste->balle.direction, vitesse_initiale);
				liste->balle.dernierJoueur = joueur1;
				collision = 1;
			}
		}
	
		/* Si la balle descend */
	
		/* Test en ordonnée */
		if (liste->balle.direction.y <0 
		&& (liste->balle.centre.y - liste->balle.rayon) >= (joueur2->raquette.centre.y + joueur2->raquette.hauteur/2) 
		&& (positionSuivante.y - liste->balle.rayon) <= (joueur2->raquette.centre.y + joueur2->raquette.hauteur/2)){
		
			/* Test en abscisse */
			if (positionSuivante.x >= (joueur2->raquette.centre.x - joueur2->raquette.largeur/2) && positionSuivante.x <= (joueur2->raquette.centre.x + joueur2->raquette.largeur/2)){
			
				/* On teste pour savoir de quel coté de la raquette la balle a rebondi */
				float testRebond = liste->balle.centre.x - joueur2->raquette.centre.x;
			
				/* La nouvelle direction en x de la balle */
				float composante_x = 0.05*(liste->balle.centre.x - joueur2->raquette.centre.x);
			
				/* Si la balle se trouve sur la partie gauche de la raquette */
				if(testRebond < 0){	
					liste->balle.direction.x = composante_x;
					liste->balle.direction.y = - liste->balle.direction.y;
				}
			
				/* Si la balle se trouve sur la partie droite de la raquette */
				if(testRebond > 0){
					liste->balle.direction.x = composante_x;
					liste->balle.direction.y = - liste->balle.direction.y;
				}
			
				/* Si la balle se trouve pile au centre de la raquette, elle rebondit verticalement et perd son facteur directeur en x*/
				if(testRebond == 0){
					liste->balle.direction.x = 0;
					liste->balle.direction.y = - liste->balle.direction.y;
				}
			
				liste->balle.direction = normaliser(liste->balle.direction);
				liste->balle.direction = multVecteur(liste->balle.direction, vitesse_initiale);
				liste->balle.dernierJoueur = joueur2;
				collision = 1;
			}
		}
	
		/* Si la balle rebondit sur les côtés */
		/* Pour la RAQUETTE HAUT */
		
			/* Côté droit (la balle va de droite à gauche) */		
			if (liste->balle.direction.x <0 && (liste->balle.centre.x - liste->balle.rayon) >= (joueur1->raquette.centre.x + joueur1->raquette.largeur/2) 
			&& (positionSuivante.x - liste->balle.rayon) <= (joueur1->raquette.centre.x + joueur1->raquette.largeur/2)){
			
				if (positionSuivante.y >= (joueur1->raquette.centre.y - joueur1->raquette.hauteur/2) && positionSuivante.y <= (joueur1->raquette.centre.y + joueur1->raquette.hauteur/2)){
					liste->balle.direction.x = - liste->balle.direction.x;
					collision = 1;
				}
			}
		
			/* Côté gauche (la balle va de gauche à droite) */		
			if (liste->balle.direction.x >0 && (liste->balle.centre.x + liste->balle.rayon) <= (joueur1->raquette.centre.x - joueur1->raquette.largeur/2)
			&& (positionSuivante.x + liste->balle.rayon) >= (joueur1->raquette.centre.x - joueur1->raquette.largeur/2)){
			
				/* Test en ordonnée */
				if (positionSuivante.y >= (joueur1->raquette.centre.y - joueur1->raquette.hauteur/2) && positionSuivante.y <= (joueur1->raquette.centre.y + joueur1->raquette.hauteur/2)){
					liste->balle.direction.x = - liste->balle.direction.x;
					collision = 1;
				}
			}
			
		/* Pour la RAQUETTE BAS */
		
			/* Côté droit (la balle va de droite à gauche) */		
			if (liste->balle.direction.x <0 && (liste->balle.centre.x - liste->balle.rayon) >= (joueur2->raquette.centre.x + joueur2->raquette.largeur/2) 
			&& (positionSuivante.x - liste->balle.rayon) <= (joueur2->raquette.centre.x + joueur2->raquette.largeur/2)){
			
				if (positionSuivante.y >= (joueur2->raquette.centre.y - joueur2->raquette.hauteur/2) && positionSuivante.y <= (joueur2->raquette.centre.y + joueur2->raquette.hauteur/2)){
					liste->balle.direction.x = - liste->balle.direction.x;
					collision = 1;
				}
			}
		
			/* Côté gauche (la balle va de gauche à droite) */		
			if (liste->balle.direction.x >0 && (liste->balle.centre.x + liste->balle.rayon) <= (joueur2->raquette.centre.x - joueur2->raquette.largeur/2)
			&& (positionSuivante.x + liste->balle.rayon) >= (joueur2->raquette.centre.x - joueur2->raquette.largeur/2)){
			
				/* Test en ordonnée */
				if (positionSuivante.y >= (joueur2->raquette.centre.y - joueur2->raquette.hauteur/2) && positionSuivante.y <= (joueur2->raquette.centre.y + joueur2->raquette.hauteur/2)){
					liste->balle.direction.x = - liste->balle.direction.x;
					collision = 1;
				}
			}
		liste = liste->next;
	}	
	return collision;
}

int collisionBallesBrique(MaillonBalle* liste, Brique* brique){
	
	int collision = 0;
	MaillonBalle* debutListe = liste;
	int nb_balles = nbBalles(liste);
	
	while(liste!=NULL && nb_balles > 0){
		
		/* ------------------------------------------------------------------------------------------------------------------------------------- */
		/* ------- Pour tester la collision entre la balle et la brique, on va comparer la position de la balle avec sa position suivante ------ */
		/* Si par exemple la balle est en dehors de la brique à un moment t, et qu'elle est dans la brique au moment t+1, alors il y a collision */
		/* ------------------------------------------------------------------------------------------------------------------------------------- */
	
		/* Calcul de la position suivante */
		Point positionSuivante = pointPlusVecteur(liste->balle.centre, liste->balle.direction);
	
		/* CAS 1 : Si la balle touche la brique par le dessus (= la balle descend) */
		/* ----------------------------------------------------------------------- */
	
		/* Test en ordonnée */
		if (liste->balle.direction.y < 0 && (liste->balle.centre.y - liste->balle.rayon) >= (brique->centre.y + brique->hauteur/2) 
		&& (positionSuivante.y - liste->balle.rayon) <= (brique->centre.y + brique->hauteur/2)){
		
			/* Test en abscisse */
			if (positionSuivante.x >= (brique->centre.x - brique->largeur/2) && positionSuivante.x <= (brique->centre.x + brique->largeur/2)){
				liste->balle.direction.y = - liste->balle.direction.y;
				collision = 1;
			}
		}
	
		/* CAS 2 : Si la balle touche la brique par le dessous (= la balle monte)  */
		/* ----------------------------------------------------------------------- */
	
		/* Test en ordonnée */
		if (liste->balle.direction.y >0 && (liste->balle.centre.y + liste->balle.rayon) <= (brique->centre.y - brique->hauteur/2) 
		&& (positionSuivante.y + liste->balle.rayon) >= (brique->centre.y - brique->hauteur/2)){
		
			/* Test en abscisse */
			if (positionSuivante.x >= (brique->centre.x - brique->largeur/2) && positionSuivante.x <= (brique->centre.x + brique->largeur/2)){
				liste->balle.direction.y = - liste->balle.direction.y;
				collision = 1;
			}
		}
	
	
		/* CAS 3 : Si la balle touche la brique par la gauche (= la balle va de gauche à droite) */
		/* ------------------------------------------------------------------------------------- */
	
		/* Test en abscisse */
		if (liste->balle.direction.x >0 && (liste->balle.centre.x + liste->balle.rayon) <= (brique->centre.x - brique->largeur/2) 
		&& (positionSuivante.x + liste->balle.rayon) >= (brique->centre.x - brique->largeur/2)){
		
			/* Test en ordonnée */
			if (positionSuivante.y >= (brique->centre.y - brique->hauteur/2) && positionSuivante.y <= (brique->centre.y + brique->hauteur/2)){
				liste->balle.direction.x = - liste->balle.direction.x;
				collision = 1;
			}
		}
		
		/* CAS 4 : Si la balle touche la brique par la droite (= la balle va de droite à gauche) */
		/* ------------------------------------------------------------------------------------- */
	
		if (liste->balle.direction.x <0 && (liste->balle.centre.x - liste->balle.rayon) >= (brique->centre.x + brique->largeur/2) 
		&& (positionSuivante.x - liste->balle.rayon) <= (brique->centre.x + brique->largeur/2)){
		
			/* Test en ordonnée */
			if (positionSuivante.y >= (brique->centre.y - brique->hauteur/2) && positionSuivante.y <= (brique->centre.y + brique->hauteur/2)){
				liste->balle.direction.x = - liste->balle.direction.x;
				collision = 1;
			}
		}
		
		/* S'il y a eu collision entre la balle et la brique, on casse la brique et on applique les bonus */
		if(collision){
		
			/* On casse la brique */
			brique->solidite --;
			/* On applique les bonus si la brique s'est cassée */
			if(brique->solidite == 0){
				appliquerBonusBrique(brique, &liste->balle, debutListe);
			}						
		}
		
		collision = 0;
		liste = liste->next;
		nb_balles--;		
	}
	return collision;
}
