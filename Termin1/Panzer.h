#pragma once
#include <GL/freeglut.h>
#include "Wuerfel.h"
class Panzer
{

public:
	Panzer();

	void schiessen();
	void show();

private:
	void createRumpf();
	void createRumpfOben();
	void createRumpfUnten();
	void createRumpfRad(float, float);

	void createTurm();
	void createRohr();
	   
};

