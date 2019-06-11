#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "particula.h"

particula::particula(vector pos, vector vel, float M, float Rad){
	posicion = pos;
	velocidad = vel;
	posini = pos;
	velini = vel;
	m = M;
	rad = Rad;
	for (int i = 0; i < 3; i++){
		f[i] = posicion.p[i];
		f[i + 3] = velocidad.p[i];
	}
}

void particula::Calcular_ele(particula ancla){
	vector L;
	float R;
	float norml;
	for (int i = 0; i < 3; i++)
		L.p[i] = ancla.posicion.p[i] - posicion.p[i];
	norml = sqrt(pow(L.p[0], 2) + pow(L.p[1], 2) + pow(L.p[2], 2));
	R = ancla.posicion.p[1] - posini.p[1];
	for (int i = 0; i < 3; i++)
		ele.p[i] = L.p[i] / norml;
	delta = norml - R;
}
void particula::Calcular_fa(particula ancla){
	vector L;
	vector Lvel;
	float R;
	for (int i = 0; i < 3; i++){
		L.p[i] = ancla.posicion.p[i] - posicion.p[i];
		Lvel.p[i] = ancla.velocidad.p[i] - velocidad.p[i];
	}
	norml = sqrt(pow(L.p[0], 2) + pow(L.p[1], 2) + pow(L.p[2], 2));
	//R = ancla.posicion.p[1] - posini.p[1];
	R = 100;
	for (int i = 0; i < 3; i++){
		ele.p[i] = L.p[i] / norml;
		elevel.p[i] = (Lvel.p[i] * L.p[i]) / norml;
	}
	delta = norml - R;
}


void particula::Calcular_Resorte(float kd, float ks){
	for (int i = 0; i < 3; i++)
		Fuerza.p[i] += (ks*delta + kd*elevel.p[i])*ele.p[i];
}
void particula::Calcular_Fuerza(float g[3], float kd, float ks, float H){
	for (int i = 0; i < 3; i++){
		Fuerza.p[i] += m*g[i]; //F=mg
		Fuerza.p[i] += -kd*velocidad.p[i];
		/*Fuerza.p[i] += delta*ks*ele.p[i];*/
	}
	// calcular derivada
	for (int i = 0; i < 3; i++){
		df[i] = velocidad.p[i];
		df[i + 3] = Fuerza.p[i] / m;
	}
	// resover eq diferencial
	for (int i = 0; i < 6; i++)
		f[i] += (df[i] * H);
	// Actualizar variable
	for (int i = 0; i < 3; i++){
		
		posicion.p[i] = f[i];
		velocidad.p[i] = f[i + 3];
		/*	cout << posicion.p[i] << " ";*/
		Fuerza.p[i] = 0;
	}
}


bool particula::Choque(vector Partplano, vector Nnormal, vector pt1, vector pt2, vector pt3){

	vector planPart;
	float prodp;


	planPart = Partplano - posicion;
	prodp = planPart + Nnormal;

	

	bool choque = false;
	bool partPlano = false;

	if (prodp < 0)
	{
		choque = true;
	}

	if (choque == true)
	{
		vector ChoqueA, ChoqueB, ChoqueC;

		ChoqueA = pt1 - posicion;
		ChoqueB = pt2 - posicion;
		ChoqueC = pt3 - posicion;

		float angulosum = (acos(ChoqueA%ChoqueB) + acos(ChoqueB%ChoqueC) + acos(ChoqueC%ChoqueA)) * 180 / 3.1416;
		cout << "el angulo es : " << angulosum << endl;
		if (360 - angulosum <= .8)
		{
			partPlano = true;
		}
	}


	return partPlano;
}


void particula::Calcular_Choque(vector Nnormal, vector Partplano){

	vector deltaV = 0;
	float Hx;
	
	float d2 = -Nnormal.p[0] * Partplano.p[0] - Nnormal.p[1] * Partplano.p[1] - Nnormal.p[2] * Partplano.p[2];

	Hx = (Nnormal.p[0] * posicion.p[0]) + (Nnormal.p[1] * posicion.p[1]) + (Nnormal.p[2] * posicion.p[2]) + d2;

	for (int i = 0; i < 3; i++)
	{
		posicion.p[i] += -(Hx*Nnormal.p[i]);
		deltaV.p[i] = -((velocidad + Nnormal)*(0.8 + 1));
		velocidad.p[i] += deltaV.p[i] * Nnormal.p[i];

		Fuerza.p[i] += 3000 * Nnormal.p[i];
	}

}


void particula::pintar(){
	glTranslatef(posicion.p[0], posicion.p[1], posicion.p[2]);
	glColor3f(1, 0, 0);
	glutSolidSphere(rad, 20, 20);

	glFlush();
}
void particula::enlace(particula ancla, particula part){
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3fv(ancla.posicion.p);
	glVertex3fv(part.posicion.p);
	glEnd();
	glFlush();
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glVertex3fv(ancla.posicion.p);
	glVertex3fv(part.posicion.p);
	glEnd();
	glFlush();
}

particula::particula()
{}

particula::~particula()
{}


