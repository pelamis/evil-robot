//TO DO:
//[V]	1. Переделать реализацию кинематических пар в ООП
//		2. Реализовать отрисовку ЗВЕНЬЕВ робота и отдельно - отрисовку КП
//		3. Наложить ограничения на углы поворота КП согласно таблице
//		4. Включить освещение.
//		5. Наложить текстуры.

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
#define A2 -20.32	
#define D1 149.09	
#define D3 433.07	
#define D5 56.25	
#define DEG_TO_RAD M_PI/180
#define SPEED  M_PI / 100000
#define SPEED2  M_PI / 10000

typedef GLdouble* PGLdouble;

typedef struct Point
{
	GLdouble	xyz[3];
	//GLdouble	RGB[3];
} Point;

typedef Point Vector;

void init();
void setMatr(GLdouble ** dst, GLdouble ** src, int ord);
void mul(GLdouble ** m1, GLdouble ** m2);
void drawAxis();
void drawBackground();

#endif