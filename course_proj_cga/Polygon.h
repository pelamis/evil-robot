#ifndef POLYGON_H_
#define POLYGON_H_

#include "commons.h"

class Polygon
{
public:
	Point *p0, *p1, *p2, *p3;
	GLdouble normal[3];
	Polygon();
	void getNormal();
	void drawPolygon();
	~Polygon();
};

#endif


