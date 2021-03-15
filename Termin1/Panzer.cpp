#include "Panzer.h"
#include <GL/freeglut.h>
#include <cmath>
#include "Wuerfel.h"

Panzer::Panzer(float xPos, float yPos, float zPos, float turmWinkel, float rohrWinkel, float rumpfWinkel)
{
	this->x = xPos;
	this->y = yPos;
	this->z = zPos;
	this->turmWinkel = turmWinkel;
	this->rohrWinkel = rohrWinkel;
	this->rumpfWinkel = rumpfWinkel;
	this->tex_2d = SOIL_load_OGL_texture("panzertexture2.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void Panzer::move(char direction) {
	if (direction == 'F') {
		double turnVal = static_cast<double> (this->rumpfWinkel % 90) / 90;
		this->z -= 0.1 * (1 - turnVal);
		if (this->rumpfWinkel < 180)
			this->x -= 0.1 * turnVal;
		else
			this->x += 0.1 * turnVal;
		
	}
	else if (direction == 'B') {
		double turnVal = static_cast<double> (this->rumpfWinkel % 90) / 90;
		this->z += 0.1 * (1 - turnVal);
		if (this->rumpfWinkel < 180)
			this->x += 0.1 * turnVal;
		else
			this->x -= 0.1 * turnVal;
	}
	else if (direction == 'L') {
		this->rumpfWinkel += 2;
		this->rumpfWinkel = this->rumpfWinkel % 360;
	}
	else if (direction == 'R') {
		this->rumpfWinkel -= 2;
		if (this->rumpfWinkel < 0)
			this->rumpfWinkel += 360;
	}
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
	glPushMatrix();
	glRotatef(this->rumpfWinkel, 0.0, 1.0, 0.0);
	createRumpf();
	glPopMatrix();

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

	// Unteren Panzerrumof mit Rädern erstellen
	createRumpfUnten();

	//Oberen Panzerrumpf mit Rädern erstellen
	createRumpfOben();
	//glDisable(GL_TEXTURE_2D);

	glPopMatrix(); // Vorigen Zustand wieder aufrufen
}

void Panzer::createRumpfOben()
{
	//// Panzer einfärben
	glColor4f(1.0, 1.0, 1.0,1.);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glEnable(GL_TEXTURE_2D);

	// rechte Seite
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.5f, 0.0f);
	glVertex3f(1.0, 0.0, 1.5);
	glTexCoord3f(1.0, 0.0, 1.5);
	glVertex3f(1.0, 0.0, -1.5);
	glTexCoord3f(1.0, 0.0, -1.5);
	glVertex3f(0.8, 0.3, -1.2);
	glTexCoord3f(0.8, 0.3, -1.2);
	glVertex3f(0.8, 0.3, 0.5);
	glTexCoord3f(0.8, 0.3, 0.5);
	glEnd();

	// linke Seite
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0, 0.0, 1.5);
	glTexCoord3f(-1.0, 0.0, 1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glTexCoord3f(-1.0, 0.0, -1.5);
	glVertex3f(-0.8, 0.3, -1.2);
	glTexCoord3f(-0.8, 0.3, -1.2);
	glVertex3f(-0.8, 0.3, 0.5);
	glTexCoord3f(-0.8, 0.3, 0.5);
	glEnd();

	// rechte Seite zw. oben und unten
	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.5f, 0.0f);
	glVertex3f(1.0, 0.0, 1.5);
	glTexCoord3f(1.0, 0.0, 1.5);
	glVertex3f(0.7, 0.0, 1.5);
	glTexCoord3f(0.7, 0.0, 1.5);
	glVertex3f(0.7, 0.0, -1.5);
	glTexCoord3f(0.7, 0.0, -1.5);
	glVertex3f(1.0, 0.0, -1.5);
	glTexCoord3f(1.0, 0.0, -1.5);
	glEnd();

	// rechte Seite zw. oben und unten
	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.5f, 0.0f);
	glVertex3f(-1.0, 0.0, 1.5);
	glTexCoord3f(-1.0, 0.0, 1.5);
	glVertex3f(-0.7, 0.0, 1.5);
	glTexCoord3f(-0.7, 0.0, 1.5);
	glVertex3f(-0.7, 0.0, -1.5);
	glTexCoord3f(-0.7, 0.0, -1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glTexCoord3f(-1.0, 0.0, -1.5);
	glEnd();

	// Vordere Schräge
	//glColor3f(0.0, 0.4, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, 1.0f);
	glVertex3f(-1.0, 0.0, 1.5);
	glTexCoord3f(-1, 0, 1.5);
	glVertex3f(1.0, 0.0, 1.5);
	glTexCoord3f(1, 0, 1.5);
	glVertex3f(0.8, 0.3, 0.5);
	glTexCoord3f(0.8, 0.3, 0.5);;
	glVertex3f(-0.8, 0.3, 0.5);
	glTexCoord3f(-0.8, 0.3, 0.5);
	glEnd();

	// Hintere Schräge
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.5f, -1.0f);
	glVertex3f(-0.8, 0.3, -1.2);
	glTexCoord3f(-0.8, 0.3, -1.2);
	glVertex3f(0.8, 0.3, -1.2);
	glTexCoord3f(0.8, 0.3, -1.2);
	glVertex3f(1.0, 0.0, -1.5);
	glTexCoord3f(1.0, 0.0, -1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glTexCoord3f(-1.0, 0.0, -1.5);
	glEnd();

	// Obere Fläche
	//glColor3f(0.0, 0.2, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.8, 0.3, 0.5);
	glTexCoord3f(-0.8, 0.3, 0.5);
	glVertex3f(0.8, 0.3, 0.5);
	glTexCoord3f(0.8, 0.3, 0.5);
	glVertex3f(0.8, 0.3, -1.2);
	glTexCoord3f(0.8, 0.3, -1.2);
	glVertex3f(-0.8, 0.3, -1.2);
	glTexCoord3f(-0.8, 0.3, -1.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Panzer::createRumpfUnten()
{
	// Die Panzerfarben einfärben
	glColor4f(1.0, 1., 1.0,1.);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glEnable(GL_TEXTURE_2D);

	// Rechte Seite
	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.7, 0.0, 1.5);
	glTexCoord3f(0.7, 0.0, 1.5);
	glVertex3f(0.7, -0.6, 0.8);
	glTexCoord3f(0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, -1.2);
	glTexCoord3f(0.7, -0.6, -1.2);
	glVertex3f(0.7, 0.0, -1.5);
	glTexCoord3f(0.7, 0.0, -1.5);
	glEnd();

	// Linke Seite
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.7, 0.0, 1.5);
	glTexCoord3f(-0.7, 0.0, 1.5);
	glVertex3f(-0.7, -0.6, 0.8);
	glTexCoord3f(-0.7, -0.6, 0.8);
	glVertex3f(-0.7, -0.6, -1.2);
	glTexCoord3f(-0.7, -0.6, -1.2);
	glVertex3f(-0.7, 0.0, -1.5);
	glTexCoord3f(-0.7, 0.0, -1.5);
	glEnd();

	// Vordere schräge
	//glColor3f(0.0, 0.7, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(1.0f, -0.5f, 0.0f);
	glVertex3f(-0.7, 0.0, 1.5);
	glTexCoord3f(-0.7, 0.0, 1.5);
	glVertex3f(-0.7, -0.6, 0.8);
	glTexCoord3f(-0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, 0.8);
	glTexCoord3f(0.7, -0.6, 0.8);
	glVertex3f(0.7, 0.0, 1.5);
	glTexCoord3f(0.7, 0.0, 1.5);
	glEnd();

	// Untere Seite
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.7, -0.6, 0.8);
	glTexCoord3f(-0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, 0.8);
	glTexCoord3f(0.7, -0.6, 0.8);
	glVertex3f(0.7, -0.6, -1.2);
	glTexCoord3f(0.7, -0.6, -1.2);
	glVertex3f(-0.7, -0.6, -1.2);
	glTexCoord3f(-0.7, -0.6, -1.2);
	glEnd();

	// Hintere Schräge
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.5f, -1.0f);
	glVertex3f(-0.7, -0.6, -1.2);
	glTexCoord3f(-0.7, -0.6, -1.2);
	glVertex3f(0.7, -0.6, -1.2);
	glTexCoord3f(0.7, -0.6, -1.2);
	glVertex3f(0.7, 0.0, -1.5);
	glTexCoord3f(0.7, 0.0, -1.5);
	glVertex3f(-0.7, 0.0, -1.5);
	glTexCoord3f(-0.7, 0.0, -1.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Vorigen Zustand speichern
	glPushMatrix();

	glColor4f(0., 0., 0., 1.);
	// Räder auf der rechten Seite
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

	// Räder auf der linken Seite
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

	// Unausgefüllten Zylinder erstellen und in Richtung front drehen
	glRotatef(drehWinkel, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), radius, radius, radBreite, 32, 32);
	
	// den Zylinder ausfüllen
	const double PI = 3.1415926535897932384626433832795;

	// Links die Fläche vom Rad
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 20)
		glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();

	// Rachts die Fläche vom Rad
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
	glColor4f(1.0, 1.0, 1.0, 1.);

	glPushMatrix();


	GLuint tex_2d = SOIL_load_OGL_texture("panzertexture2.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);


	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLES);
	//front
	glNormal3f(0., 0., 1.);
		glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0., -0.5);
		glTexCoord3f(-0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord3f(0.5, 0.5, -0.5);

		glNormal3f(0., 0., 1.);
		glVertex3f(-0.5, 0., -0.5);
		glTexCoord3f(-0.5, 0., -0.5);
		glVertex3f(0.5, 0., -0.5);
		glTexCoord3f(0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord3f(0.5, 0.5, -0.5);


	//hinten
		glNormal3f(0., 0., -1.);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0., 0.5);
		glTexCoord3f(-0.5, 0., 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord3f(0.5, 0.5, 0.5);

		glNormal3f(0., 0., -1.);
		glVertex3f(-0.5, 0., 0.5);
		glTexCoord3f(-0.5, 0., 0.5);
		glVertex3f(0.5, 0., 0.5);
		glTexCoord3f(0.5, 0., 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord3f(0.5, 0.5, 0.5);



	//rechte seite
		glNormal3f(1., 0., 0.);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0., -0.5);
		glTexCoord3f(0.5, 0., -0.5);

		glNormal3f(1., 0., 0.);
		glVertex3f(0.5, 0., -0.5);
		glTexCoord3f(0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0., 0.5);
		glTexCoord3f(0.5, 0., 0.5);

	//linke seite
		glNormal3f(-1., 0., 0.);
		glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0., -0.5);
		glTexCoord3f(-0.5, 0., -0.5);

		glNormal3f(-1., 0., 0.);
		glVertex3f(-0.5, 0., -0.5);
		glTexCoord3f(-0.5, 0., -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0., 0.5);
		glTexCoord3f(-0.5, 0., 0.5);


	//deckel
		glNormal3f(0., 1., 0.);
		glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord3f(0.5, 0.5, -0.5);
		
		glNormal3f(0., 1., 0.);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord3f(0.5, 0.5, -0.5);
		
	glEnd();

	glDisable(GL_TEXTURE_2D);


	//einstiegsloch
	glPushMatrix();
	glColor4f(0.5, 0.5, 0.5, 1.);
		glTranslatef(0.25, 0.625, 0.25);
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

	glNormal3f(0.0, 1.0, 0.0);
	GLUquadricObj* quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.1, 0.1, 2.0, 32, 32);

	glPopMatrix();
}
