#pragma once
#ifndef LINK_H_
#define _LINK_H_

#include "commons.h"
#include "KPairArray.h"

class Link
{
private:
	GLdouble ** T0;
	Point endPoint;
	Point *vertexes;
	GLdouble side, len;
	//material:light
	//material:texture
public:
	Link();
	~Link();
	void buildMesh();
	void reInit(GLdouble **T0, , GLdouble side, GLdouble len);
	void drawLink();
	void reGetT0andAxis(GLdouble **T0, GLdouble ax, GLdouble ay, GLdouble az);
};

#endif
