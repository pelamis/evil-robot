#pragma once
#ifndef LINK_H_
#define _LINK_H_

#include "commons.h"
#include "KPairArray.h"

class Link
{
private:
	GLdouble ** T0;
	GLdouble ** T1;
	Point *vertexes;
	GLdouble side1, side2;
	//material:light
	//material:texture
public:
	Link();
	~Link();
	void buildMesh();
	void reInit(GLdouble **T0, GLdouble **T1, GLdouble side1, GLdouble side2);
	void drawLink();
	void reGetT0andT1(GLdouble **T0, GLdouble **T1);
};

#endif
