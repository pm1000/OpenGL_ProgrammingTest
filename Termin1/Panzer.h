#pragma once
#include <GL/freeglut.h>

class Panzer
{

public:
	Panzer();

	void schiessen();
	

private:
	void createRumpf();
	void createTurm();
	void createRohr();
	   
};

