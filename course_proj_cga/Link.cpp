#include "Link.h"

Link::Link()
{
	vertexes = NULL;
	this->T0 = NULL;
	this->axis = new GLdouble[3];
	this->side = 0;
	this->len = 0;
}

void Link::reInit(GLdouble **T0, GLdouble ax, GLdouble ay, GLdouble az, GLdouble side, GLdouble len)
{
	int i,j;
	if (vertexes != NULL) delete vertexes;
	vertexes = new Point[8];
	for (i = 0; i < 8; i++)
	for (j = 0; j < 3; j++) vertexes[i].xyz[j] = 0;
	this->T0 = T0;
	this->axis[0] = ax;
	this->axis[1] = ay;
	this->axis[2] = az;
	this->side = side;
	this->len = len;
}


Link::~Link()
{
	delete vertexes;
}

//BEWARE OF MORONS!!!
void Link::buildMesh()
{
	int i,j;
	int vSequence1[2] = {0, 3}, vSequence2[4] = {1, 2};
	double x, y, z;

	if (vertexes == NULL) vertexes = new Point[8];

	for (i = 0; i < 4; i++)
		for (j=0;j<3;j++)
			vertexes[i].xyz[j] = 0;

	vertexes[0].xyz[1] = side;
	vertexes[1].xyz[0] = side;
	vertexes[2].xyz[1] = - side; //����������� ��� i-� ����� (���. ������) ������������� �����
	vertexes[3].xyz[0] = - side;

	for (i = 0; i < 4; i++) vertexes[i].xyz[2] = 0;
	
	

	//for (i = 0; i < 4; i++)
	//for (j = 0; j < 3; j++) vertexes[i].xyz[j] = T0[j][3]; //��������� ������ ������ �������� ���������� ������ "�������" ��������� ������
	//
	////x coords
	//for (i = 0; i < 2; i++)
	//{
	//	vertexes[i].xyz[0] -= side / 2;
	//	vertexes[i + 2].xyz[0] += side / 2;
	//}
	//
	////z coords
	//for (i = 0; i < 2; i++)
	//{
	//	vertexes[vSequence1[i]].xyz[2] -= side / 2;
	//	vertexes[vSequence2[i]].xyz[2] += side / 2;
	//}
	//// second "basement"
	//for (i = 0; i < 4; i++)
	//{
	//	vertexes[4 + i].xyz[0] = vertexes[i].xyz[0]+ endPoint[0];
	//	vertexes[4 + i].xyz[1] = endPoint[1];
	//	vertexes[4 + i].xyz[2] = vertexes[i].xyz[2]+endPoint[2];
	//}
	i=0;
	for (i = 0; i < 4; i++)
	{
		x = vertexes[i].xyz[0];
		y = vertexes[i].xyz[1];
		z = vertexes[i].xyz[2];
		
		vertexes[i].xyz[0] = x*T0[0][0] + y*T0[0][1] + z*T0[0][2] + T0[0][3];
		vertexes[i].xyz[1] = x*T0[1][0] + y*T0[1][1] + z*T0[1][2] + T0[1][3];
		vertexes[i].xyz[2] = x*T0[2][0] + y*T0[2][1] + z*T0[2][2] + T0[2][3];
		
	}
}

void Link::drawLink()
{
	int vSequence[] = {0,1,2,3//,
						// 7,6,5,4 ,
						// 3,2,6,7,
						// 4,5,1,0,
						// 1,5,6,2,
						 /*3,7,4,0*/};
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

void Link::reGetT0(GLdouble **T0)
{
	int i;
	if (this->T0 != NULL)
	{
		for (i = 0; i < 4;i++)
		if (this->T0[i] != NULL) delete this->T0[i];
		delete this->T0;
	}

	this->T0 = T0;
}
