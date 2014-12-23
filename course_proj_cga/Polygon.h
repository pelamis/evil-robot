#ifndef POLYGON_H_
#define POLYGON_H_

#include "commons.h"

class Polygon
{
public:
	Point *p0, *p1, *p2, *p3;
	Vector v0, v1, normal;
	Polygon(Point* p0, Point* p1, Point* p2, Point* p3);
	void getNormal();
	void drawNormal();
	void drawPolygon();
	~Polygon();
};

#endif


