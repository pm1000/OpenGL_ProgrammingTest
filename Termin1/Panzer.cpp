#include "Panzer.h"
#include <GL/freeglut.h>
#include <cmath>
#include "Wuerfel.h"

Panzer::Panzer(float xPos, float yPos, float zPos, float turmWinkel, float rohrWinkel)
{
	this->x = xPos;
	this->y = yPos;
	this->z = zPos;
	this->turmWinkel = turmWinkel;
	this->rohrWinkel = rohrWinkel;

}

Kugel* Panzer::schiessen()
{
	Kugel* k = new Kugel(x, y + 0.25*0.9 + 0.3 + 0.9, z - 0.3, turmWinkel, rohrWinkel);
	return k;
}

void Panzer::show()
{
	// Vorigen Zustand speichern
	glPushMatrix();

	// Den Panzer anhand der Pos im Raum an die richtige Pos bewegen
	glTranslatef(x, y + 0.9, z);

	// Rumpf des Panzers erstellen
	createRumpf();

	// Den Turm und das Rohr positionieren
	glTranslatef(0.0, 0.3, -0.3);
	glScalef(0.9, 0.9, 0.9);
	glRotatef(turmWinkel, 0.0, 1.0, 0.0);
	createTurm();
	createRohr();

	// Vorigen Zustand wieder holen
	glPopMatrix();
}





float Panzer::getTurmWinkel()
{
	return turmWinkel;
}

void Panzer::setTurmWinkel(float value)
{
	turmWinkel = value;
}

float Panzer::getRohrWinkel()
{
	return rohrWinkel;
}

void Panzer::setRohrWinkel(float value)
{
	rohrWinkel = (value <= 6 && value >= -12) ? value : rohrWinkel;
}





void Panzer::createRumpf()
{
	glPushMatrix(); //Vorigen Zustand sichern

	//texture setzen
	glColor4f(0., 0., 0., 1.);
	//GLuint tex_2d = SOIL_load_OGL_texture("panzertexture.png", SOIL_LOAD_AUTO,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//	/*SOIL_LOAD_AUTO,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_INVERT_Y);*/
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//glBindTexture(GL_TEXTURE_2D, tex_2d);
	//glEnable(GL_TEXTURE_2D);

	// Unteren Panzerrumof mit R�dern erstellen
	createRumpfUnten();

	//Oberen Panzerrumpf mit R�dern erstellen
	createRumpfOben();
	//glDisable(GL_TEXTURE_2D);

	glPopMatrix(); // Vorigen Zustand wieder aufrufen
}

void Panzer::createRumpfOben()
{
	//// Panzer einf�rben
	glColor3f(0.0, 0.7, 0.0);
	//GLuint tex_2d = SOIL_load_OGL_texture("panzertexture2.png", SOIL_LOAD_AUTO,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	///*SOIL_LOAD_AUTO,
	//SOIL_CREATE_NEW_ID,
	//SOIL_FLAG_INVERT_Y);*/
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	///*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);*/

	//glBindTexture(GL_TEXTURE_2D, tex_2d);
	//glEnable(GL_TEXTURE_2D);

	//glBegin(GL_TEXTURE_2D);
	// rechte Seite
	glBegin(GL_QUADS);
	glVertex3f(1.0, 0.0, 1.5);
	glTexCoord3f(1.0, 0.0, 1.5);
	glVertex3f(1.0, 0.0, -1.5);
	glTexCoord3f(1.0, 0.0, -1.5);
	glVertex3f(0.8, 0.3, -1.2);
	glTexCoord3f(0.8, 0.3, -1.2);
	glVertex3f(0.8, 0.3, 0.5);
	glTexCoord3f(0.8, 0.3, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// linke Seite
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, 0.0, 1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glVertex3f(-0.8, 0.3, -1.2);
	glVertex3f(-0.8, 0.3, 0.5);
	glEnd();

	// rechte Seite zw. oben und unten
	glBegin(GL_POLYGON);
	
	glTexCoord3f(1.0, 0.0, 1.5);
	glTexCoord3f(0.7, 0.0, 1.5);
	glTexCoord3f(0.7, 0.0, -1.5);
	glTexCoord3f(1.0, 0.0, -1.5);
	glVertex3f(1.0, 0.0, 1.5);
	glVertex3f(0.7, 0.0, 1.5);
	glVertex3f(0.7, 0.0, -1.5);
	glVertex3f(1.0, 0.0, -1.5);
	glEnd();

	// rechte Seite zw. oben und unten
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, 0.0, 1.5);
	glVertex3f(-0.7, 0.0, 1.5);
	glVertex3f(-0.7, 0.0, -1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glEnd();

	// Vordere Schr�ge
	//glColor3f(0.0, 0.4, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, 0.0, 1.5);
	glTexCoord3f(-1, 0, 1.5);
	glVertex3f(1.0, 0.0, 1.5);
	glTexCoord3f(1, 0, 1.5);
	glVertex3f(0.8, 0.3, 0.5);
	glTexCoord3f(0.8, 0.3, 0.5);;
	glVertex3f(-0.8, 0.3, 0.5);
	glTexCoord3f(-0.8, 0.3, 0.5);
	glEnd();

	// Hintere Schr�ge
	glBegin(GL_POLYGON);
	glVertex3f(-0.8, 0.3, -1.2);
	glVertex3f(0.8, 0.3, -1.2);
	glVertex3f(1.0, 0.0, -1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glEnd();

	// Obere Fl�che
	//glColor3f(0.0, 0.2, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.8, 0.3, 0.5);
	glVertex3f(0.8, 0.3, 0.5);
	glVertex3f(0.8, 0.3, -1.2);
	glVertex3f(-0.8, 0.3, -1.2);
	glEnd();

}

void Panzer::createRumpfUnten()
{
	// Die Panzerfarben einf�rben
	//glColor3f(0.0, 0.5, 0.0);

	// Rechte Seite
	glBegin(GL_POLYGON);
	glVertex3f(0.7, 0.0, 1.5);
	glVertex3f(0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, -1.2);
	glVertex3f(0.7, 0.0, -1.5);
	glEnd();

	// Linke Seite
	glBegin(GL_POLYGON);
	glVertex3f(-0.7, 0.0, 1.5);
	glVertex3f(-0.7, -0.6, 0.8);
	glVertex3f(-0.7, -0.6, -1.2);
	glVertex3f(-0.7, 0.0, -1.5);
	glEnd();

	// Vordere schr�ge
	//glColor3f(0.0, 0.7, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.7, 0.0, 1.5);
	glVertex3f(-0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, 0.8);
	glVertex3f(0.7, 0.0, 1.5);
	glEnd();

	// Untere Seite
	glBegin(GL_POLYGON);
	glVertex3f(-0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, -1.2);
	glVertex3f(-0.7, -0.6, -1.2);
	glEnd();

	// Hintere Schr�ge
	glBegin(GL_POLYGON);
	glVertex3f(-0.7, -0.6, -1.2);
	glVertex3f(0.7, -0.6, -1.2);
	glVertex3f(0.7, 0.0, -1.5);
	glVertex3f(-0.7, 0.0, -1.5);
	glEnd();

	// Vorigen Zustand speichern
	glPushMatrix();

	// R�der auf der rechten Seite
	glTranslatef(0.7, -0.5, 0.0);
	createRumpfRad(0.2, 90); // mittleres
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	createRumpfRad(0.2, 90); // vorderes
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.75);
	createRumpfRad(0.2, 90); //hinteres
	glPopMatrix();
	glPopMatrix();

	// R�der auf der linken Seite
	glPushMatrix();
	glTranslatef(-0.7, -0.5, 0.0);
	createRumpfRad(0.2, -90); // mittleres
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	createRumpfRad(0.2, -90); // vorderes
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.75);
	createRumpfRad(0.2, -90); //hinteres
	glPopMatrix();

	// Vorigen Zustand wiederherstellen
	glPopMatrix();
}

void Panzer::createRumpfRad(float radBreite, float drehWinkel)
{
	float radius = 0.3;

	// Vorigen Zustand speichern
	glPushMatrix();

	// Farbe setzen
	//glColor3f(0.1, 0.1, 0.1);

	// Unausgef�llten Zylinder erstellen und in Richtung front drehen
	glRotatef(drehWinkel, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), radius, radius, radBreite, 32, 32);
	
	// den Zylinder ausf�llen
	const double PI = 3.1415926535897932384626433832795;

	// Links die Fl�che vom Rad
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 20)
		glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();

	// Rachts die Fl�che vom Rad
	glTranslatef(0.0, 0.0, radBreite);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 20)
		glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();

	// Vorigen Zustand wieder abrufen
	glPopMatrix();
}







void Panzer::createTurm()
{
	//farbe
	glColor4f(0.1, .5, 0.1, 1.);

	glPushMatrix();


	glBegin(GL_TRIANGLES);
	//front
		glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0., -0.5);
		glTexCoord3f(-0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord3f(0.5, 0.5, -0.5);

	
		glVertex3f(-0.5, 0., -0.5);
		glVertex3f(0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, -0.5);


	//hinten
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0., 0.5);
		glVertex3f(0.5, 0.5, 0.5);

		glVertex3f(-0.5, 0., 0.5);
		glVertex3f(0.5, 0., 0.5);
		glVertex3f(0.5, 0.5, 0.5);



	//rechte seite
		glColor4f(0.15, .1, 0.1, 1.);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0., -0.5);

		glVertex3f(0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0., 0.5);

	//linke seite
		glColor4f(0., 0., 0., 1.);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0., -0.5);

		glVertex3f(-0.5, 0., -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0., 0.5);


	//deckel
		glColor4f(0.3, 0.3, 0.3, 1.);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		
	glEnd();


	//einstiegsloch
	glPushMatrix();
		glTranslatef(0.25, 0.625, 0.25);
		glColor4f(0., 0., 0., 1.);
		Wuerfel(0.2);
	glPopMatrix();

	createRohr();

	glPopMatrix();
}

void Panzer::createRohr()
{
	glTranslatef(0., 0.25, 0.0);
	glColor4f(0., 0., 0., 1.);
	Wuerfel(0.2);

	glPushMatrix();
	glRotatef(rohrWinkel, 1., 0., 0.);
	//glRotatef(-30., 1., 0., 0.);

	GLUquadricObj* quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.1, 0.1, 2.0, 32, 32);

	glPopMatrix();
}
