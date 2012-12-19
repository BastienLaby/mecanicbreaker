#include "Texture.h"

/* Fonctions */

Texture CreerTexture(int id_texture, Point coord, float largeur, float hauteur){
	Texture t;
	t.id_texture = id_texture;
	t.coordonnee = coord;
	t.largeur = largeur;
	t.hauteur = hauteur;
	
	return t;
}

GLenum getFormat(SDL_Surface* p){
	GLenum format;
	switch(p->format->BytesPerPixel){
	case 1 : 
		format = GL_RED;
		break;
	case 3 :
		format = GL_RGB;
		break;
	case 4 :
		format = GL_RGBA;
		break;
	default :
		fprintf(stderr, "Format des pixels de l'image non pris en charge \n");
		return EXIT_FAILURE;
	}
	return format;
}

GLuint* chargementImagesTheme1(){

	int i, nb_img;
	nb_img = 6;

	char* images[nb_img];
	images[0] = "img/theme1/fond.png";
	images[1] = "img/theme1/tileset.png";
	images[2] = "img/theme1/tilesetdeco.png";
	images[3] = "img/theme1/echap.jpg";
	images[4] = "img/cursor1.png";
	images[5] = "img/cursor2.png";
	
	SDL_Surface* p_images[nb_img];
	
	for (i=0; i<nb_img; i++){
		p_images[i] = IMG_Load(images[i]); 
		if(p_images[i] == NULL){
 			fprintf(stderr, "erreur de chargement de l'image %s\n", images[i]);	
 		}	
	}
	
	GLuint* t_images = (GLuint*)malloc(nb_img*sizeof(GLuint));
	glGenTextures(nb_img, t_images); /* Génération du nombre de textures voulues */
	
	/* Parametrage de toutes les images */
	GLenum format;
		
	for (i=0; i<nb_img; i++){ /* pour chaque texture, on importe l'image dans openGL */
		glBindTexture(GL_TEXTURE_2D, t_images[i]); /* Attache d'une texture à un quai */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* Application du filtre de redimension */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		format = getFormat(p_images[i]); /* Récupération du format de l'image (fonction locale) */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_images[i]->w, p_images[i]->h, 0, format, GL_UNSIGNED_BYTE, p_images[i]->pixels); /* Envoi de l'image à OpenGL (quai en question) */
		glBindTexture(GL_TEXTURE_2D, 0); /* Libérer le quai */
		
		SDL_FreeSurface(p_images[i]);
	}
	
	return t_images;
	
}

GLuint* chargementImagesTheme2(){

	int i, nb_img;
	nb_img = 6;

	char* images[nb_img];
	images[0] = "img/theme2/fond.png";
	images[1] = "img/theme2/tileset.png";
	images[2] = "img/theme2/tilesetdeco.png";
	images[3] = "img/theme2/echap.jpg";
	images[4] = "img/cursor1.png";
	images[5] = "img/cursor2.png";
	
	SDL_Surface* p_images[nb_img];
	
	for (i=0; i<nb_img; i++){
		p_images[i] = IMG_Load(images[i]); 
		if(p_images[i] == NULL){
 			fprintf(stderr, "erreur de chargement de l'image %s\n", images[i]);	
 		}	
	}
	
	GLuint* t_images = (GLuint*)malloc(nb_img*sizeof(GLuint));
	glGenTextures(nb_img, t_images); /* Génération du nombre de textures voulues */
	
	/* Parametrage de toutes les images */
	GLenum format;
		
	for (i=0; i<nb_img; i++){ /* pour chaque texture, on importe l'image dans openGL */
		glBindTexture(GL_TEXTURE_2D, t_images[i]); /* Attache d'une texture à un quai */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* Application du filtre de redimension */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		format = getFormat(p_images[i]); /* Récupération du format de l'image (fonction locale) */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_images[i]->w, p_images[i]->h, 0, format, GL_UNSIGNED_BYTE, p_images[i]->pixels); /* Envoi de l'image à OpenGL (quai en question) */
		glBindTexture(GL_TEXTURE_2D, 0); /* Libérer le quai */
		
		SDL_FreeSurface(p_images[i]);
	}
	
	return t_images;
	
}

/*-----------------------------------------------*/
/* --------- FONCTIONS DE DESSIN --------------- */

void dessinCercle(int full){

	GLenum type;
	if(full==0){
		type=GL_LINE_LOOP;
	}
	else{
		type=GL_POLYGON;
	}
	int i=0;
	float mycos=0;
	float mysin=0;
	
	glBegin(type);
		for (i=0 ; i<SEGMENTS ; i++) { 
			mycos = cos(i*2*M_PI/SEGMENTS);
			mysin = sin(i*2*M_PI/SEGMENTS);
			glVertex2f(mycos, mysin);
		}
	glEnd();
}

void dessinrepere(){
	glColor3ub(255,255,255);
	glBegin(GL_LINES);
		glVertex2f(0, 10);
		glVertex2f(0, -10);
		glVertex2f(-10, 0);
		glVertex2f(10, 0);
	glEnd();
}

void dessinCarre(int full){

	GLenum type;
	if(full==0){
		type=GL_LINE_LOOP;
	}
	else{
		type=GL_QUADS;
	}
	glBegin(type);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();
}

void dessinEngrenage1(GLuint texture){
	
}

void dessinEngrenage2(GLuint texture){

}
