/*
	wuerfel.cpp definiert einen Würfel über seine 6 Seiten
	Last Update:  13.10.2011   W.-D. Groch
*/
#include <GL/freeglut.h>
#include "Rechteck.h"


void Rechteck(GLfloat x, GLfloat y, GLfloat z)
{
	glBegin(GL_POLYGON);   //Vorderseite
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);	//ROT
	glVertex3f(-x / 2.0f, -y / 2.0f, +z / 2.0f);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+x / 2.0f, -y / 2.0f, +z / 2.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+x / 2.0f, +y / 2.0f, +z / 2.0f);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-x / 2.0f, +y / 2.0f, +z / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+x / 2.0f, -y / 2.0f, +z / 2.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+x / 2.0f, -y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);	//CYAN
	glVertex3f(+x / 2.0f, +y / 2.0f, -z / 2.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+x / 2.0f, +y / 2.0f, +z / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //CYAN
	glVertex3f(+x / 2.0f, +y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+x / 2.0f, -y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-x / 2.0f, -y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-x / 2.0f, +y / 2.0f, -z / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-x / 2.0f, +y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-x / 2.0f, -y / 2.0f, -z / 2.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT	
	glVertex3f(-x / 2.0f, -y / 2.0f, +z / 2.0f);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-x / 2.0f, +y / 2.0f, +z / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-x / 2.0f, +y / 2.0f, +z / 2.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+x / 2.0f, +y / 2.0f, +z / 2.0f);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //CYAN
	glVertex3f(+x / 2.0f, +y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-x / 2.0f, +y / 2.0f, -z / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-x / 2.0f, -y / 2.0f, -z / 2.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+x / 2.0f, -y / 2.0f, -z / 2.0f);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+x / 2.0f, -y / 2.0f, +z / 2.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT
	glVertex3f(-x / 2.0f, -y / 2.0f, +z / 2.0f);
	glEnd();

	return;
}

