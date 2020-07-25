#include "Panzer.h"

Panzer::Panzer()
{
	void createRumpf();
	void createTurm();
	void createRohr();
}

void Panzer::schiessen()
{
}

void Panzer::createRumpf()
{
}

void Panzer::createTurm()
{
	//farbe
	glColor4f(0., 1., 0., 1.);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-0.25, 0., 0.25);
	glVertex3f(-0.25, 0., -0.25);
	glVertex3f(0.25, 0., 0.25);
	glVertex3f(0.25, 0., -0.25);
	
	glEnd();



}

void Panzer::createRohr()
{
}
