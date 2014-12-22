#include "Link.h"

Link::Link()
{
	vertexes = NULL;
	this->T0 = NULL;
	this->axis = new GLdouble[3];
	this->offset = new GLdouble[3];
	this->side1 = 0;
	this->side2 = 0;
	this->len = 0;
}

void Link::reInit(GLdouble **T0, GLdouble *ax, GLdouble *offs, GLdouble side1, GLdouble side2, GLdouble len)
{
	int i,j;
	if (vertexes != NULL) delete vertexes;
	vertexes = new Point[8];
	for (i = 0; i < 8; i++)
	for (j = 0; j < 3; j++) vertexes[i].xyz[j] = 0;
	this->T0 = T0;
	for (i = 0; i < 3; i++)
	{
		this->axis[i] = ax[i]; 
		this->offset[i] = offs[i];
	}
	this->side1 = side1;
	this->side2 = side2;
	this->len = len;
}


Link::~Link()
{
	delete vertexes;
	delete axis;
	delete offset;
}

//BEWARE OF MORONS!!!
void Link::buildMesh()
{
	int i,j;
	int coords[4][2] = { { -side1*sin(M_PI_4), side2*cos(M_PI_4) }, { side1*cos(M_PI_4), side2*sin(M_PI_4)}, 
						{ side1*sin(M_PI_4), -side2*cos(M_PI_4) }, { -side1*cos(M_PI_4), -side2*sin(M_PI_4) } };
	double x, y, z;

	if (vertexes == NULL) vertexes = new Point[8];

	for (i = 0; i < 4; i++)
		for (j=0;j<3;j++)
			vertexes[i].xyz[j] = 0;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (axis[j] == 1)
				{
					vertexes[i].xyz[(j + 1) % 3] = coords[i][0]+offset[(j + 1) % 3];
					vertexes[i].xyz[(j + 2) % 3] = coords[i][1]+offset[(j + 2) % 3];
					vertexes[i].xyz[j] = offset[j];

					vertexes[4 + i].xyz[(j + 1) % 3] = vertexes[i].xyz[(j + 1) % 3];
					vertexes[4 + i].xyz[(j + 2) % 3] = vertexes[i].xyz[(j + 2) % 3];
					vertexes[4 + i].xyz[j] = len + offset[j];
				}
			}
			
		}
	
	for (i = 0; i < 8; i++)
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
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
