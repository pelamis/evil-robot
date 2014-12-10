#pragma once
#ifndef KINEMATICPAIR_H_
#define KINEMATICPAIR_H_

#include "commons.h"

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
	int checkQ();
	void drawKP();					
	void moveKP();					
	void setDQ(GLdouble newDQ);
	bool checkMove();
	void moveEnable();
	void moveDisable();
	void moveSwitch();
};

#endif
