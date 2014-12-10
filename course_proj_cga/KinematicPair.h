#pragma once
#ifndef KINEMATICPAIR_H_
#define KINEMATICPAIR_H_

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
	void setAMatrix();				
	int setQ(GLdouble q);							
	void moveKP();					
	void setDQ(GLdouble newDQ);
	bool checkMove();
	void moveSwitch();
};

#endif
