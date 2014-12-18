#include "KPairArray.h"


KPairArray::KPairArray()
{
	int i;
	this->length = KP_NUMBER;
	this->array = new KinematicPair[this->length];
	
	GLdouble a_init[KP_NUMBER] = { 0, A1, A2, 0, 0, 0 };
	GLdouble q_init[KP_NUMBER] = { M_PI_2, 0, M_PI_2, 0, 0, 0 };
	GLdouble d_init[KP_NUMBER] = { 0, D1, 0, D3, 0, D5 };
	GLdouble alpha_init[KP_NUMBER] = { -M_PI_2, 0, M_PI_2, -M_PI_2, M_PI_2, 0 };
	GLdouble minq_init[KP_NUMBER] = { -160, -225, -45, -110, -100, -266 };
	GLdouble maxq_init[KP_NUMBER] = { 160, 45, 225, 170, 100, 266 };
	for (i = 0; i < length; i++) array[i].reInit(a_init[i], q_init[i], d_init[i], 
		alpha_init[i], DEG_TO_RAD*minq_init[i], DEG_TO_RAD*maxq_init[i]);
}


KPairArray::~KPairArray()
{
	int i;
	for (i = 0; i < length; i++) array[i].~KinematicPair();
	delete array;
}

int KPairArray::getLength()
{
	return this->length;
}

GLdouble ** KPairArray::getTForPair(int pairNumber)
{
	//Note: T must be cleaned by the caller after using
	char i, j;
	GLdouble** T = new PGLdouble[4];
	for (i = 0; i < 4; i++) T[i] = new GLdouble[4];
	for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++) T[i][j] = (i == j);
	if (pairNumber<length)
	for (i = 0; i <= pairNumber; i++) mul(T, array[i].getAPtr());
	return T;
}

KinematicPair & KPairArray::getPair(int pairNumber)
{
	return array[pairNumber];
}

void KPairArray::drawPair(int pairNumber)
{
	int i;
	GLdouble **T = getTForPair(pairNumber);
	
	glPointSize(10.0);
	glBegin(GL_POINTS);
		glColor3d(0, 1, 1);
		glVertex3d(T[0][3], T[1][3], T[2][3]);
	glEnd();
	for (i = 0; i < 4; i++) delete T[i];
	delete T;
}