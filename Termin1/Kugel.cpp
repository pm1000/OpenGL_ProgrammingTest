#include "Kugel.h"
#include <GL/freeglut.h>
#include <cmath>


Kugel::Kugel(float x, float y, float z, float turmWinkel, float rohrWinkel)
{
	// Parameter speichern
	this->rootX = x;
	this->rootY = y;
	this->rootZ = z;
	this->turmWinkel = turmWinkel;
	this->rohrWinkel = rohrWinkel;

	// Attribute festlegen
	bisherigeAufrufe = 0.0;
}





bool Kugel::show()
{
	// Prüfen ob die Kugel noch fliegen soll (true=darf fliegen; false=löschen)
	if (bisherigeAufrufe > MAX_SCHUSSWEITE) return false;

	// Wenn die Kugel noch fliegen darf
	bisherigeAufrufe += GESCHWINDIGKEIT;

	// Kugel modellieren mit Werten des Abschusses
	glPushMatrix();

	glTranslatef(rootX, rootY, rootZ);
	glRotatef(turmWinkel, 0.0, 1.0, 0.0);
	glRotatef(rohrWinkel, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, bisherigeAufrufe);

	createKugel();

	glPopMatrix();
}





void Kugel::createKugel()
{
	float radius = 0.05;
	float kugelLaenge = 0.5;

	// Vorigen Zustand speichern
	glPushMatrix();

	// Farbe setzen
	glColor3f(0.1, 0.1, 0.1);

	// Unausgefüllten Zylinder erstellen und in Richtung front drehen
	gluCylinder(gluNewQuadric(), radius, radius, kugelLaenge, 32, 32);

	// den Zylinder ausfüllen
	const double PI = 3.1415926535897932384626433832795;

	// Hintere Fläche der kugel
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 20)
		glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();

	// Vordere Fläche der Kugel
	glTranslatef(0.0, 0.0, kugelLaenge);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 20)
		glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();

	// Vorigen Zustand wieder abrufen
	glPopMatrix();
}

