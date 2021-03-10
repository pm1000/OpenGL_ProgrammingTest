#pragma once
#include <GL/freeglut.h>
#include "GL/SOIL.h"
#include "Kugel.h"
class Panzer
{

public:
	Panzer(float xPos, float yPos, float zPos, float turmWinkel, float rohrWinkel, float rumpfWinkel);

	Kugel * schiessen();
	void show();

	void move(char direction);

	float getTurmWinkel();
	void setTurmWinkel(float value);

	float getRohrWinkel();
	void setRohrWinkel(float value);

private:

	float turmWinkel;
	float rohrWinkel;
	float x, y, z;
	float rumpfWinkel;

	GLuint tex_2d;


	void createRumpf();
	void createRumpfOben();
	void createRumpfUnten();
	void createRumpfRad(float, float);

	void createTurm();
	void createRohr();
	   
};

