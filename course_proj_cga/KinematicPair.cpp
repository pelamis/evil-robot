#include "KinematicPair.h"

KinematicPair::KinematicPair()
{
	int i, j;

	this->a = 0;
	this->q = 0;
	this->d = 0;
	this->alpha = 0;
	this->minAngle = 0;
	this->maxAngle = 0;
	this->dq = M_PI / 100000;
	this->isMoving = false;

	this->A = new GLdouble*[4];
	for (j = 0; j < 4; j++) this->A[j] = new GLdouble[4];

	for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++) this->A[i][j] = 0;

	//setAMatrix();
}

void KinematicPair::reInit(GLdouble a, GLdouble q, GLdouble d, GLdouble alpha, GLdouble minAngle, GLdouble maxAngle)
{
	int i, j;

	this->a = a;
	this->q = q;
	this->d = d;
	this->alpha = alpha;
	this->minAngle = minAngle;
	this->maxAngle = maxAngle;
	this->dq = M_PI / 10000;
	this->isMoving = false;

	this->A=new GLdouble*[4];
	for (j = 0; j < 4; j++) this->A[j] = new GLdouble[4];

	for (i = 0; i < 4;i++)
	for (j = 0; j < 4; j++) this->A[i][j] = 0;

	setAMatrix();
}


KinematicPair::~KinematicPair()
{
	int i;
	for (i = 0; i < 4; i++) delete this->A[i];
	delete this->A;
}

void KinematicPair::setAMatrix()
{
	GLdouble s, c, ac, as;
	s = sin(q);
	c = cos(q);
	as = sin(alpha);
	ac = cos(alpha);

	A[0][0] = c;
	A[1][0] = s;
	A[0][1] = -ac*s;
	A[1][1] = ac*c;
	A[0][2] = as*s;
	A[1][2] = -as*c;
	A[2][1] = as;
	A[2][2] = ac;
	A[0][3] = a*c;
	A[1][3] = a*s;
	A[2][3] = d;
	A[3][3] = 1;
}

int KinematicPair::setQ(GLdouble q)
{
	//qWasNotCorrect == -1 => q is less than lower bound
	//qWasNotCorrect == 1  => q is greater than upper bound
	int qWasNotCorrect = 0;
	if (q >= this->minAngle && q <= this->maxAngle) this->q = q;
	else {
		if (q < minAngle)
		{
			printf_s("New q has reached the bounds: suggesting q as min...\n");
			this->q = minAngle;
			qWasNotCorrect = -1;
		}
		else {
			printf_s("New q has reached the bounds: suggesting q as max...\n");
			this->q = maxAngle;
			qWasNotCorrect = 1;
		}
	}
	return qWasNotCorrect;
}

void KinematicPair::moveKP()
{
	int result;
	if (checkMove())
	{
		result = setQ(q + dq);
		if (result == 1) setDQ(-dq);
		if (result == -1) setDQ(abs(dq));
	}
	setAMatrix();
}

void KinematicPair::setDQ(GLdouble newDQ)
{
	this->dq = newDQ;
}

bool KinematicPair::checkMove()
{
	return (isMoving);
}

void KinematicPair::moveSwitch()
{
	if (!isMoving) printf_s("KP is moving now: min=%lf \t max=%lf\n", (180 / M_PI)*minAngle, (180 / M_PI)*maxAngle);
	else printf_s("KP has been stopped\n");
	isMoving = !isMoving;
}
