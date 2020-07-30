#include "Kamera.h"
#include <GL/freeglut.h>

Kamera::Kamera(float eyeX, float eyeY, float eyeZ, float dirX, float dirY, float dirZ)
{
	this->eyeX = eyeX;
	this->eyeY = eyeY;
	this->eyeZ = eyeZ;
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

void Kamera::show()
{
	gluLookAt(eyeX, eyeY, eyeZ, dirX, dirY, dirZ, 0.0, 1.0, 0.0);
}

void Kamera::setEyePosition(float x, float y, float z)
{
	this->eyeX = x;
	this->eyeY = y;
	this->eyeZ = z;
}

void Kamera::setTargetPosition(float x, float y, float z)
{
	this->dirX = x;
	this->dirY = y;
	this->dirZ = z;
}
