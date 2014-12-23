#include "Polygon.h"


Polygon::Polygon(Point* p0, Point* p1, Point* p2, Point* p3)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	getNormal();
}

void Polygon::getNormal()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		v0.xyz[i] = p1->xyz[i] - p0->xyz[i];
		v1.xyz[i] = p3->xyz[i] - p0->xyz[i];
	}
	normal.xyz[0] = (v0.xyz[1] * v1.xyz[2] - v0.xyz[2] * v1.xyz[1]);
	normal.xyz[1] = (v0.xyz[0] * v1.xyz[2] - v0.xyz[2] * v1.xyz[0]);
	normal.xyz[2] = (v0.xyz[0] * v1.xyz[1] - v0.xyz[1] * v1.xyz[0]);
}

void Polygon::drawPolygon()
{
	glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		glNormal3dv(normal.xyz);
		glVertex3dv(p0->xyz);
		glVertex3dv(p1->xyz);
		glVertex3dv(p2->xyz);
		glVertex3dv(p3->xyz);
	glEnd();
}

void Polygon::drawNormal()
{
	Point center;
	center.xyz[0] = p0->xyz[0] + (v0.xyz[0] + v1.xyz[0]) / 2;
	center.xyz[1] = p0->xyz[1] + (v0.xyz[1] + v1.xyz[1]) / 2;
	center.xyz[2] = p0->xyz[2] + (v0.xyz[2] + v1.xyz[2]) / 2;
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
		glVertex3dv(center.xyz);
		glVertex3d(center.xyz[0] + normal.xyz[0],
				   center.xyz[1] + normal.xyz[1],
			  	   center.xyz[2] + normal.xyz[2]);
	glEnd();
}

Polygon::~Polygon()
{
}
