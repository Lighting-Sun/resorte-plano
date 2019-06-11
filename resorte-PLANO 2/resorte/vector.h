#include <iostream>

using namespace std;

#pragma once
class vector
{
public:
	
	float p[3];
	
	vector(float x = 0, float y = 0, float z = 0);



	vector operator^(vector);//producto cruz
	vector operator-(vector);//resta
	float operator+(vector); //producto punto

	float operator%(vector); //coseno del angulo
	

	vector normalizar();

	void mostrar();

	~vector();
};

