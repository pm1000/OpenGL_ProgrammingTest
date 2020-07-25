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


	void createTurm();
	void createRohr();
	   
};

