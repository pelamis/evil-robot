//TO DO:
//1. Переделать реализацию кинематических пар в ООП
//2. Реализовать отрисовку ЗВЕНЬЕВ робота и отдельно - отрисовку КП
//3. Наложить ограничения на углы поворота КП согласно таблице
//4. Включить освещение.
//5. Наложить текстуры.

#define _USE_MATH_DEFINES

#include "glew.h"
#include "glfw3.h"
#include "math.h"
#include <gl\GLU.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

#define KP_NUMBER 6
#define MAXANGLE PI/2
#define MAX 100
#define A1 431.8	//215.9
#define A2 20.32	//-10.16
#define D1 149.09	//74.545
#define D3 433.07	//216.535
#define D5 56.25	//28.125

GLdouble PI = M_PI;
GLdouble A = SCREEN_WIDTH / 4.0, B = 0.0, C = SCREEN_HEIGHT / 2.0, D = C;
GLfloat lcolr0[3] = { 0, 0, 1 },
n0[3] = { 1, 1, 0 },
pos0[4] = { 10, 10, 10, 0 },
a0[4] = { 0, 0, 0, 1 },
d0[4] = { 1, 1, 1, 1 },
s0[4] = { 1, 1, 1, 1 },
sd0[3] = { 0, 0, -1 };
GLfloat ma[4] = { 0.2, 0.5, 0.5, 1 };
GLfloat md[4] = { 0.2, 0.2, 0.8, 1 };
GLfloat ms[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shine[1] = { 63 };
GLfloat ascene[4] = { 0, 0.5, 0.5, 1 };
typedef GLdouble* PGLdouble;

typedef struct Point
{
	GLdouble	x;
	GLdouble	y;
	GLdouble	z;
	GLdouble	RGB[3];
} Point;

class KP
{
	GLdouble ** A;
	GLdouble a, q, d, alpha, minRotAngle, maxRotAngle;
};

class Light {
public:
	GLfloat *RGB,
		*normal,
		*position,
		*amb,
		*diff,
		*spec,
		*spdir,
		exp, cutoff, kc, kl, kq;

	char e = 0;

	Light(GLfloat *color, GLfloat *n, GLfloat *pos, GLfloat *a, GLfloat *d, GLfloat *s, GLfloat *sdir,
		GLfloat e, GLfloat coff, GLfloat k_c, GLfloat k_l, GLfloat k_q);
	void SetColor(GLfloat *color);
	void SetGeom(GLfloat *n, GLfloat *pos, GLfloat *sdir, GLfloat e, GLfloat coff);
	void SetLightConf(GLfloat *a, GLfloat *d, GLfloat *s, GLfloat k_c, GLfloat k_l, GLfloat k_q);
	void Enable();
};

void buildAMatr(KP *nodeArray);
void init(KP *nodeArray);
void setMatr(GLdouble ** dst, GLdouble ** src, int ord);
void mul(GLdouble ** m1, GLdouble ** m2);

void drawAxis();
void drawKP(KP *nodeArray);
void drawBackground();
