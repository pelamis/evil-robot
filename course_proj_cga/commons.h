#define _USE_MATH_DEFINES

#include "glew.h"
#include "glfw3.h"
#include "math.h"
#include <gl\GLU.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define KP_NUMBER 5
#define MAXANGLE 50
#define MAX 100
#define HEIGHT 300
#define LEN1 200
#define LEN2 300
//alpha_1,3 = -pi/2; alpha_2,4 = 0

GLdouble PI = M_PI;
GLdouble A = SCREEN_WIDTH / 4.0, B = 0.0, C = SCREEN_HEIGHT / 2.0, D = C;

typedef GLdouble Vector[4];
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
	GLdouble ** A;
//	GLdouble DH[4][4];
	GLdouble a, alpha, q,d;
}KP;

void buildCS(KP *nodeArray);
void buildAMatr(KP *KPair,int kpnum);
//GLdouble * convert(Matrix input);
void init(KP *nodeArray);
void setMatr(GLdouble ** dst, GLdouble ** src, int ord);
//void setQ(KP *KPair, int kpnum);
void mul(GLdouble ** m1, GLdouble ** m2);
//GLdouble* sharedNormal(GLdouble *v1, GLdouble *v2);

void drawAxis();
void drawKP(KP *nodeArray);

GLdouble vector(GLdouble *v1, GLdouble *v2);

void movedbg();