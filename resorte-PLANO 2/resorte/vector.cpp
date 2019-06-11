#include "vector.h"

vector::vector(float x, float y, float z)
{
	p[0] = x;
	p[1] = y;
	p[2] = z;
}


vector vector::operator^(vector k) {   //producto cruz
	vector temp;
	temp.p[0] = (p[1]*k.p[2]) - (k.p[1]*p[2]);
	temp.p[1] = -((p[0]*k.p[2]) - (k.p[0]*p[2]));
	temp.p[2] = (p[0]*k.p[1]) - (k.p[0]*p[1]);
	return temp;
}
vector vector::operator-(vector k) {   //distancia entre vectores
	vector temp;
	temp.p[0] = p[0] - k.p[0];
	temp.p[1] = p[1] - k.p[1];
	temp.p[2] = p[2] - k.p[2];
	return temp;
}

float vector::operator+(vector k) {   //producto punto
	float temp;

	temp = (p[0] * k.p[0]) + (p[1] * k.p[1]) + (p[2] * k.p[2]);

	return temp;
}

float vector::operator%(vector k){  //coseno angulo

	float temp;
	float punto = (p[0] * k.p[0]) + (p[1] * k.p[1]) + (p[2] * k.p[2]);

	float normau = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
	float normav = sqrt(k.p[0] * k.p[0] + k.p[1] * k.p[1] + k.p[2] * k.p[2]);

	temp = punto / (normau*normav);

	return temp;

}

vector vector::normalizar(){
	vector nuev;
	float m = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);

	
	for (int i = 0; i < 3; i++)
	{
		nuev.p[i] = p[i] / m;
	}

	return nuev;
	
}

void vector::mostrar() {
	cout << "(" << p[0] << "," << p[1] << "," << p[2] << ")" << endl;
}

vector::~vector()
{
}
