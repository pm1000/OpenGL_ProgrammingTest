#pragma once
class Kamera
{
private:
	float eyeX, eyeY, eyeZ;
	float dirX, dirY, dirZ;

public:
	Kamera(float eyeX, float eyeY, float eyeZ, float dirX, float dirY, float dirZ);


	void show();
	void setEyePosition(float x, float y, float z);
	void setTargetPosition(float x, float y, float z);
};

