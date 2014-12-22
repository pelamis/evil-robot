#pragma once
#ifndef LINK_H_
#define _LINK_H_

#include "commons.h"
#include "KPairArray.h"

class Link
{
private:
	GLdouble ** T0;
	GLdouble *axis,*offset;
	Point *vertexes;
	GLdouble side1, side2, len;
	//material:light
	//material:texture
public:
	Link();
	~Link();
	void buildMesh();
	void reInit(GLdouble **T0, GLdouble *ax, GLdouble *offs, GLdouble side1, GLdouble side2, GLdouble len);
	void drawLink();
	void reGetT0(GLdouble **T0);
};

#endif
