#include "Link.h"


Link::Link()
{
	vertexes = NULL;
	this->T0 = NULL;
	this->T1 = NULL;
	this->side1 = 0;
	this->side2 = 0;
}

void Link::reInit(GLdouble **T0, GLdouble **T1, GLdouble side1, GLdouble side2)
{
	if (vertexes != NULL) delete vertexes;
	vertexes = new Point[8];
	this->T0 = T0;
	this->T1 = T1;
	this->side1 = side1;
	this->side2 = side2;
}


Link::~Link()
{
	delete vertexes;
}

void Link::buildMesh()
{
	int i,j,k;
	if (vertexes == NULL) vertexes = new Point[8];
	vertexes[0].xyz[0] = T0[0][3] - side1 / 2;
	vertexes[0].xyz[1] = T0[1][3];
	vertexes[0].xyz[2] = T0[2][3] - side2 / 2;
	
	vertexes[4].xyz[0] = T1[0][3] - side1 / 2;
	vertexes[4].xyz[1] = T1[1][3];
	vertexes[4].xyz[2] = T1[2][3] - side2 / 2;

	vertexes[1].xyz[0] = T0[0][3] - side1 / 2;
	vertexes[1].xyz[1] = T0[1][3];
	vertexes[1].xyz[2] = T0[2][3] + side2 / 2;

	vertexes[5].xyz[0] = T1[0][3] - side1 / 2;
	vertexes[5].xyz[1] = T1[1][3];
	vertexes[5].xyz[2] = T1[2][3] + side2 / 2;

	vertexes[2].xyz[0] = T0[0][3] + side1 / 2;
	vertexes[2].xyz[1] = T0[1][3];
	vertexes[2].xyz[2] = T0[2][3] + side2 / 2;

	vertexes[6].xyz[0] = T1[0][3] + side1 / 2;
	vertexes[6].xyz[1] = T1[1][3];
	vertexes[6].xyz[2] = T1[2][3] + side2 / 2;

	vertexes[3].xyz[0] = T0[0][3] + side1 / 2;
	vertexes[3].xyz[1] = T0[1][3];
	vertexes[3].xyz[2] = T0[2][3] - side2 / 2;

	vertexes[7].xyz[0] = T1[0][3] + side1 / 2;
	vertexes[7].xyz[1] = T1[1][3];
	vertexes[7].xyz[2] = T1[2][3] - side2 / 2;
}

void Link::drawLink()
{
	glLineWidth(1.0);
	//glBegin(GL_LINES);
//	glColor3d(1, 1, 0);
	//	glVertex3d(T0[0][3], T0[1][3], T0[2][3]);
	//	glVertex3d(T1[0][3], T1[1][3], T1[2][3]);
//	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[0].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[1].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[2].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[3].xyz);

	glVertex3dv(vertexes[7].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[6].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[5].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[4].xyz);

	glVertex3dv(vertexes[3].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[2].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[6].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[7].xyz);

	glVertex3dv(vertexes[4].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[5].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[1].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[0].xyz);

	glVertex3dv(vertexes[1].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[5].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[6].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[2].xyz);

	glVertex3dv(vertexes[3].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[7].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[4].xyz);
	glColor3d(1, 1, 1);
	glVertex3dv(vertexes[0].xyz);

	glEnd();
}

void Link::reGetT0andT1(GLdouble **T0, GLdouble **T1)
{
	int i;
	if (this->T0 != NULL)
	{
		for (i = 0; i < 4;i++)
		if (this->T0[i] != NULL) delete this->T0[i];
		delete this->T0;
	}
	if (this->T1 != NULL)
	{
		for (i = 0; i < 4;i++)
		if (this->T1[i] != NULL) delete this->T1[i];
		delete this->T1;
	}
	this->T0 = T0;
	this->T1 = T1;
}
