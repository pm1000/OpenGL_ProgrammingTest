#pragma once
class Kugel
{
private:
	const float MAX_SCHUSSWEITE = 30.0;
	const float GESCHWINDIGKEIT = 0.5;

	float rootX;
	float rootY;
	float rootZ;
	float turmWinkel;
	float rohrWinkel;

	float bisherigeAufrufe;

	void createKugel();

public:
	Kugel(float, float, float, float, float);

	bool show();
};

