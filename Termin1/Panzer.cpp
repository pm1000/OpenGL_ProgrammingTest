#include "Panzer.h"

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
	glColor4f(0., 1., 0., 0.5);

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.25, 0.9, 0.25);
		glVertex3f(-0.25, -0.9, 0.25);
		glVertex3f(0.25, 0.9, 0.25);
	//glVertex3f(0.25, 0., 0.25);
	
	glEnd();


}

void Panzer::createRohr()
{
}
