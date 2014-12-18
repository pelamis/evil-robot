#ifndef KINEMATICPAIR_H_
#define KINEMATICPAIR_H_

#include "commons.h"

class KinematicPair
{
private:
	GLdouble ** A;
	GLdouble a, q, d, alpha, minAngle, maxAngle, dq;
	bool isMoving;
public:
	KinematicPair();
	void reInit(GLdouble a, GLdouble q, GLdouble d, GLdouble alpha, GLdouble minAngle, GLdouble maxAngle);
	~KinematicPair();
	void setAMatrix();
	GLdouble ** getAPtr();
	int setQ(GLdouble q);							
	void moveKP();					
	void setDQ(GLdouble newDQ);
	bool checkMove();
	void moveSwitch();
};

#endif
