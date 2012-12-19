#include "balle.h"
#include "Joueur.h"
#include "Bordure.h"
#include "Brique.h"

int collisionBallesBordures(MaillonBalle* liste, Bordure bordureG, Bordure bordureD);
int collisionBallesRaquettes(MaillonBalle* liste, Joueur* joueur1, Joueur* joueur2);
int collisionBallesBrique(MaillonBalle* liste, Brique* brique);
