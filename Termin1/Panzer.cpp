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
	// Hier Code zum übergeben der aktuellen Daten für die Kugel
	// Kugelkonstruktor: new Kugel(rootX, rootY, rootZ, turmWinkel, rohrWinkel)
	// x, y, z sind die Koordinaten wo die Kugel ihren Ursprung hat
	// turmWinkel und rohrWinkel können einfach übergeben werden
	// Schiessen kannst du dann mit Leertaste
	Kugel* k = new Kugel(x, y + 0.25*0.9 + 0.3 + 0.9, z - 0.3, turmWinkel, rohrWinkel);
	//Kugel* k = new Kugel(0.0, 1.0, -3.0, 25.0, 25.0); // Beispielwerte für Testkugel


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

	// Unteren Panzerrumof mit Rädern erstellen
	//glScalef(2.0, 2.0, 2.0);
	createRumpfUnten();

	//Oberen Panzerrumpf mit Rädern erstellen
	createRumpfOben();

	glPopMatrix(); // Vorigen Zustand wieder aufrufen
}

void Panzer::createRumpfOben()
{
	// Panzer einfärben
	glColor3f(0.0, 0.7, 0.0);

	// rechte Seite
	glBegin(GL_POLYGON);
	glVertex3f(1.0, 0.0, 1.5);
	glVertex3f(1.0, 0.0, -1.5);
	glVertex3f(0.8, 0.3, -1.2);
	glVertex3f(0.8, 0.3, 0.5);
	glEnd();

	// linke Seite
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, 0.0, 1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glVertex3f(-0.8, 0.3, -1.2);
	glVertex3f(-0.8, 0.3, 0.5);
	glEnd();

	// rechte Seite zw. oben und unten
	glBegin(GL_POLYGON);
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

	// Vordere Schräge
	glColor3f(0.0, 0.4, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, 0.0, 1.5);
	glVertex3f(1.0, 0.0, 1.5);
	glVertex3f(0.8, 0.3, 0.5);
	glVertex3f(-0.8, 0.3, 0.5);
	glEnd();

	// Hintere Schräge
	glBegin(GL_POLYGON);
	glVertex3f(-0.8, 0.3, -1.2);
	glVertex3f(0.8, 0.3, -1.2);
	glVertex3f(1.0, 0.0, -1.5);
	glVertex3f(-1.0, 0.0, -1.5);
	glEnd();

	// Obere Fläche
	glColor3f(0.0, 0.2, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.8, 0.3, 0.5);
	glVertex3f(0.8, 0.3, 0.5);
	glVertex3f(0.8, 0.3, -1.2);
	glVertex3f(-0.8, 0.3, -1.2);
	glEnd();

}

void Panzer::createRumpfUnten()
{
	// Die Panzerfarben einfärben
	glColor3f(0.0, 0.5, 0.0);

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

	// Vordere schräge
	glColor3f(0.0, 0.7, 0.0);
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

	// Hintere Schräge
	glBegin(GL_POLYGON);
	glVertex3f(-0.7, -0.6, -1.2);
	glVertex3f(0.7, -0.6, -1.2);
	glVertex3f(0.7, 0.0, -1.5);
	glVertex3f(-0.7, 0.0, -1.5);
	glEnd();

	// Vorigen Zustand speichern
	glPushMatrix();

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
	glColor3f(0.1, 0.1, 0.1);

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
	glColor4f(0.1, .5, 0.1, 1.);

	glPushMatrix();

	glBegin(GL_TRIANGLES);
	//front
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0., -0.5);
		glVertex3f(0.5, 0.5, -0.5);
	
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
