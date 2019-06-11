#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"
#ifdef _WIN32
#include "glut.h"
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
#pragma once
class particula{
public:
	float m;
	float df[6];
	float f[6];
	float rad;
	vector posicion;
	vector posini;
	vector velocidad;
	vector velini;
	vector Fuerza;
	vector ele;
	float norml = 0;
	vector elevel;
	float delta = 0;
	particula(vector pos, vector vel, float M, float Rad);
	particula();
	~particula();
	void pintar();
	void triangulo();
	void enlace(particula ancla, particula part);
	void Calcular_ele(particula ancla);
	void Calcular_fa(particula ancla);
	void Calcular_Fuerza(float g[3], float kd, float ks, float H);
	void Calcular_Choque(float g[3], float kd, float ks, float H);
	void Calcular_Resorte(float kd, float ks);

	bool Choque(vector Partplano, vector Nnormal, vector pt1, vector pt2, vector pt3);
	void Calcular_Choque(vector Nnormal, vector Partplano);

	

};

