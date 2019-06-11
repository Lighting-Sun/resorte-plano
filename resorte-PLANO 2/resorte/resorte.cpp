#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"
#include "particula.h"
#ifdef _WIN32
#include "glut.h"
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
float r = 5, t = 0, g[3] = { 0, -9.8, 0 }, m = 10, h = 0.05, Kd = 1, Ks = 3, d = 0;
int i;
double movZ = 0;
double movY = 0;
double giro = 0;
double giro2 = 0;
/***********************************/

vector P1, P2, P3, n, P1P2, P1P3;

bool traspasar = true;

////
vector PlanPart;

vector pCual;

float prodp;

float probando = 0, eps = 5;

////

///rebote

float Hx;
float Ke = 0.8;
vector deltaV = 0;
float Kr = 30000;


///// ------ delimitacion plano

vector normal;

vector ChoqueA, ChoqueB, ChoqueC;

///

void Plano(vector n, vector p, float d){
	//float x, y, z;
	//x = p.p[0] - 50;
	//z = p.p[2] - 50;
	//y = -(d + (n.p[0] * x) + (n.p[2] * z)) / n.p[1];
	//float x2, y2, z2;
	//x2 = p.p[0] + 50;
	//z2 = p.p[2] - 50;
	//y2 = -(d + (n.p[0] * x2) + (n.p[2] * z2)) / n.p[1];
	//float x3, y3, z3;
	//x3 = p.p[0] + 50;
	//z3 = p.p[2] + 50;
	//y3 = -(d + (n.p[0] * x3) + (n.p[2] * z3)) / n.p[1];
	//float x4, y4, z4;
	//x4 = p.p[0] - 50;
	//z4 = p.p[2] + 50;
	//y4 = -(d + (n.p[0] * x4) + (n.p[2] * z4)) / n.p[1];

	//glColor4ub(255, 255, 255, 100);
	//glBegin(GL_QUADS);
	//glVertex3f(x, y, z);
	//glVertex3f(x2, y2, z2);
	//glVertex3f(x3, y3, z3);
	//glVertex3f(x4, y4, z4);





	glEnd();
}
void Triangulo(vector p1, vector p2, vector p3){
	glBegin(GL_TRIANGLES);
	glColor4ub(255, 0, 0, 255);
	glVertex3fv(p1.p);
	glColor4ub(0, 255, 0, 255);
	glVertex3fv(p2.p);
	glColor4ub(0, 0, 255, 255);
	glVertex3fv(p3.p);
	glEnd();
}
/***********************************/
void TransformacionesCamara();
void IniciarCG(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300, 300, -300, 300, -300, 300);
	glMatrixMode(GL_MODELVIEW);
}
vector pos = { 0, 100, 77.94f };
vector pos2 = { 45, 100, 0 };
vector pos3 = { -45, 100, 0 };
vector pos4 = { 0, 100, 0 };
vector vel = { 0, 0, 0 };
vector vel2 = { 0, 0, 5};
particula part(pos, vel, m, r);
particula part2(pos2, vel, m, r);
particula part3(pos3, vel, m, r);
vector va = { 0, 150, 77.94f };
vector va2 = { 45, 150, 0 };
vector va3 = { -45, 150, 0 };
//anclas
particula ancla(va, vel, m, r);
particula ancla2(va2, vel, m, r);
particula ancla3(va3, vel, m, r);
//esfera cayendo
particula part4(pos4, vel2, m, r);

void TransformacionesCamara(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1, 0.001, 10000);
	glTranslated(0, movY, movZ);
	/*gluLookAt(400, 400, 400, 0, 0, 0, 0, 1, 0);*/
	gluLookAt(800, 800, 800, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}
void ejes(){
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3d(0, -180, 0);
	glVertex3d(0, 180, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(0, 0, -180);
	glVertex3d(0, 0, 180);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3d(-180, 0, 0);
	glVertex3d(180, 0, 0);
	glEnd();
}
void Graficar(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glRotated(giro, 0, 1, 0);
	TransformacionesCamara();
	ejes();
	glPushMatrix();
	part.pintar();

	glPopMatrix();
	glPushMatrix();
	part2.pintar();

	glPopMatrix();
	glPushMatrix();
	part3.pintar();

	glPopMatrix();
	glPushMatrix();
	part4.pintar();

	glPopMatrix();
	Plano(n, P1, d);//grafica el plano
	Triangulo(P1, P2, P3);
	part.enlace(ancla, part);
	part2.enlace(ancla2, part2);
	part3.enlace(ancla3, part3);
	part.enlace(part2, part);
	part2.enlace(part3, part2);
	part3.enlace(part, part3);
	glutSwapBuffers();
}

void OnKey(unsigned char key, int x, int y){
	switch (key)
	{
	case 'i': case 'I':
		movZ += 1;
		break;
	case 'k': case 'K':
		movZ -= 1;
		break;
	case 'o': case 'O':
		movY += 0.4f;
		break;
	case 'l': case 'L':
		movY -= 0.4f;
		break;
	case 'a': case 'A':
		giro += 0.4f;
		break;
	case 'd': case 'D':
		giro -= 0.4f;
		break;
	case 's': case 'S':
		giro2 -= 0.4f;
		break;
	}
	if (key == 27)
		exit(0);
	if (key == '1')
		part.Fuerza.p[1] += -200;
	if (key == '2')
		part2.Fuerza.p[1] += -200;
	if (key == '3')
		part3.Fuerza.p[1] += -200;

	glutPostRedisplay();
}


void calc(){
	part.Calcular_fa(ancla);
	part.Calcular_Resorte(Kd, Ks);
	part.Calcular_fa(part2);
	part.Calcular_Resorte(Kd, Ks);
	part.Calcular_fa(part3);
	part.Calcular_Resorte(Kd, Ks);
	part.Calcular_Fuerza(g, Kd, Ks, h);
}

void calc2(){
	part2.Calcular_fa(ancla2);
	part2.Calcular_Resorte(Kd, Ks);
	part2.Calcular_fa(part);
	part2.Calcular_Resorte(Kd, Ks);
	part2.Calcular_fa(part3);
	part2.Calcular_Resorte(Kd, Ks);
	part2.Calcular_Fuerza(g, Kd, Ks, h);
}
void calc3(){
	part3.Calcular_fa(ancla3);
	part3.Calcular_Resorte(Kd, Ks);
	part3.Calcular_fa(part2);
	part3.Calcular_Resorte(Kd, Ks);
	part3.Calcular_fa(part);
	part3.Calcular_Resorte(Kd, Ks);
	part3.Calcular_Fuerza(g, Kd, Ks, h);
}
void calc4(){

	part4.Calcular_Fuerza(g, Kd, Ks, h);
	
	if (part4.Choque(part.posicion,normal,part.posicion,part2.posicion,part3.posicion) == true)
	{
		part4.Calcular_Choque(normal,part.posicion);
	}


	



}

void CalculoChoque(){
	calc(); calc2(); calc3();
	P1 = part.posicion;
	P2 = part2.posicion;
	P3 = part3.posicion;
	P1P2 = P2 - P1;
	P1P3 = P3 - P1;
	PlanPart = part4.posicion - part.posicion;
	n = P1P2^P1P3;
	d = -n.p[0] * P2.p[0] - n.p[1] * P2.p[1] - n.p[2] * P2.p[2];
	normal = n.normalizar();

	calc4();






}

////
void OnTimerGL(int id){
	CalculoChoque();

		//cout << "La particula choco a: " << probando << endl;
		//despues = part4.posicion;



	
		//
	
		//cout << "Cruza el plano a: " << prodp << endl;
		//antes = part4.posicion;

		glutPostRedisplay();
		glutTimerFunc(10, OnTimerGL, 1);

	t += h;
}



int main(int argc, char **argv){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Programa Basico");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutKeyboardFunc(OnKey);
	IniciarCG();
	glutDisplayFunc(Graficar);
	glutTimerFunc(1, OnTimerGL, 1);
	glutMainLoop();
	system("pause");
	return 0;
}