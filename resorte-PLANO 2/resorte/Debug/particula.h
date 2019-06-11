#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"

using namespace std;

#pragma once




class particula
{
public:
	
	//float r = 15, t = 0, h = 0.1, f[6], Kd = 5, Ks = 5;

	//int i;

	//float A[3], X0[3], X[3], V0[3], V[3], F[3], g[3], f[6], df[6], L[3], ele[3], normL, delta, R;

	static float m;
	static float df[6];
	static float f[6];

	static float rad;
	static vector posicion;
	static vector velocidad;
	static vector Fuerza;





	particula(vector pos, vector vel, float M , float Rad);

	particula();
	~particula();
	void Calcular_Fuerza(float kd);
	void Calcular_derivada();
	void Resolver_EcDif(float H);
	void Actualizar_Var();

};

