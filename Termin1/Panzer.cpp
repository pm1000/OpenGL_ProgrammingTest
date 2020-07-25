#include "Panzer.h"
#include "Wuerfel.h"

Panzer::Panzer()
{
}

void Panzer::schiessen()
{
}

void Panzer::show()
{
	createRumpf();
	createTurm();
	createRohr();
}





void Panzer::createRumpf()
{

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
	glTranslatef(0., 0.25, 0.6);
	glColor4f(0., 0., 0., 1.);
	Wuerfel(0.2);

	glPushMatrix();
	glRotatef(-30., 1., 0., 0.);

	GLUquadricObj* quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.1, 0.1, 1.5, 32, 32);

	glPopMatrix();
}
