//TO DO:
//[V]	1. ���������� ���������� �������������� ��� � ���
//		2. ����������� ��������� ������� ������ � �������� - ��������� ��
//		3. �������� ����������� �� ���� �������� �� �������� �������
//		4. �������� ���������.
//		5. �������� ��������.

#ifndef COMMONS_H_
#define COMMONS_H_

#define _USE_MATH_DEFINES

#include "glew.h"
#include "glfw3.h"
#include "math.h"
#include <gl\GLU.h>
#include "stdafx.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

#define KP_NUMBER 6
#define MAX 100
#define A1 431.8	
#define A2 20.32	
#define D1 149.09	
#define D3 433.07	
#define D5 56.25	
#define DEG_TO_RAD M_PI/180
typedef GLdouble* PGLdouble;

typedef struct Point
{
	GLdouble	x;
	GLdouble	y;
	GLdouble	z;
	GLdouble	RGB[3];
} Point;

typedef struct KinemPair
{
public:
	GLdouble ** A;
	GLdouble a,q,d,alpha,minAngle,maxAngle;
	bool isMoving;
}KP;

void buildAMatr(KP *nodeArray);
void init(KP *nodeArray);
void setMatr(GLdouble ** dst, GLdouble ** src, int ord);
void mul(GLdouble ** m1, GLdouble ** m2);

void drawAxis();
void drawKP(KP *nodeArray);
void drawBackground();

#endif