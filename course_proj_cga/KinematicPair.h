#pragma once
#include "commons.h"
//#define ROT_SPEED=M_

class KinematicPair
{
public:
	GLdouble ** A;
	GLdouble a, q, d, alpha, minAngle, maxAngle, dq;
	bool isMoving;

	KinematicPair();
	void reInit(GLdouble a, GLdouble q, GLdouble d, GLdouble alpha, GLdouble minAngle, GLdouble maxAngle);				//CHK
	~KinematicPair();
	void setAMatrix();				//CHK
	int setQ(GLdouble q);			//CHK
	int checkQ();
	void drawKP();					//CHK
	void moveKP();					//CHK
	void setDQ(GLdouble newDQ);
	bool checkMove();
	void moveEnable();
	void moveDisable();
	void moveSwitch();
};

