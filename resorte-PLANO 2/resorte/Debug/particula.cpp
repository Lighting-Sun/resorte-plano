#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>

#include "particula.h"




particula::particula(vector pos, vector vel, float M, float Rad)
{
	posicion = pos;
	velocidad = vel;
	m = M;
	rad = Rad;
}

particula::particula()
{
}

particula::~particula()
{
}

void Calcular_Fuerza(float kd){

	float g[3] = { 0, 9.8, 0 };

	for (int i = 0; i<3; i++)
	{
		particula::Fuerza.p[i] = 0;
		particula::Fuerza.p[i] += particula::m*g[i]; //F=mg
		particula::Fuerza.p[i] += -kd*particula::velocidad.p[i];
		//F[i] += delta*Ks*ele[i];
		
	}


}

void Calcular_derivada()
{
	for (int i = 0; i<3; i++)
	{
		particula::df[i] = particula::velocidad.p[i];
		particula::df[i + 3] = particula::Fuerza.p[i] / particula::m;
	}
}

void Resolver_EcDif(float H)
{
	for (int i = 0; i<6; i++)
	{
		particula::f[i] += (particula::df[i] * H);
	}
	/*T += h;*/
}

void Actualizar_Var()
{
	for (int i = 0; i<3; i++)
	{
		particula::posicion.p[i] = particula::f[i];
		particula::velocidad.p[i] = particula::f[i + 3];
		cout << particula::posicion.p[i] << " ";
	}
	cout << endl;

}




