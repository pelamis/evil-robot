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
	int vSequence1[4] = { 0, 3, 4, 7 }, vSequence2[4] = { 1, 2, 5, 6 };
	double x, y, z, t00,t01,t02,t10,t11,t12,t21,t22;

	if (vertexes == NULL) vertexes = new Point[8];

	for (i = 0; i < 4;i++)
	for (j = 0; j < 3; j++)
	{
	//	vertexes[i].xyz[j] = T0[j][3];
		vertexes[4 + i].xyz[j] = T1[j][3];
	}

	for (i = 0; i < 2; i++)
	{
		vertexes[i].xyz[0] = -side1 / 2;
		vertexes[4 + i].xyz[0] -= -side1 / 2;
		vertexes[i + 2].xyz[0] = side1 / 2;
		vertexes[6 + i].xyz[0] = side1 / 2;
	}
		
	for (i = 0; i < 4; i++)
	{
		vertexes[vSequence1[i]].xyz[2] = -side2 / 2;
		vertexes[vSequence2[i]].xyz[2] = side2 / 2;

	}

	for (i = 0; i < 8; i++)
	{
		x = vertexes[i].xyz[0];
		y = vertexes[i].xyz[1];
		z = vertexes[i].xyz[2];
		//if (i < 4)
		//{
			vertexes[i].xyz[0] = x*T0[0][0] + y*T0[0][1] + z*T0[0][2] + T0[0][3];
			vertexes[i].xyz[1] = x*T0[1][0] + y*T0[1][1] + z*T0[1][2] + T0[1][3];
			vertexes[i].xyz[2] = x*T0[2][0] + y*T0[2][1] + z*T0[2][2] + T0[2][3];
		//}
		//else {
		//	vertexes[i].xyz[0] = x*T0[0][0] + y*T0[0][1] + z*T0[0][2] + T1[0][3];
		//	vertexes[i].xyz[1] = x*T0[1][0] + y*T0[1][1] + z*T0[1][2] + T1[1][3];
		//	vertexes[i].xyz[2] = x*T0[2][0] + y*T0[2][1] + z*T0[2][2] + T1[2][3];
		//}
	}
}

void Link::drawLink()
{
	int vSequence[] = {0,1,2,3,
						 7,6,5,4 ,
						 3,2,6,7,
						 4,5,1,0,
						 1,5,6,2,
						 3,7,4,0};
	int i;
	glLineWidth(1.0);
	//glBegin(GL_LINES);
//	glColor3d(1, 1, 0);
	//	glVertex3d(T0[0][3], T0[1][3], T0[2][3]);
	//	glVertex3d(T1[0][3], T1[1][3], T1[2][3]);
//	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		for (i = 0; i < sizeof(vSequence)/sizeof(int); i++) glVertex3dv(vertexes[vSequence[i]].xyz);
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
