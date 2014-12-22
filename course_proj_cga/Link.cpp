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
						 7,6,5,4,
						 3,2,6,7,
						 4,5,1,0,
						 1,5,6,2,
						 3,7,4,0};
	int i,j,ax;
	GLdouble x1, x2, y1, y2, z1, z2;
	for (i = 0; (axis[i] != 1)&&(i < 3); i++);
	ax=i;
	glLineWidth(1.0);
	//glBegin(GL_LINES);
//	glColor3d(1, 1, 0);
	//	glVertex3d(T0[0][3], T0[1][3], T0[2][3]);
	//	glVertex3d(T1[0][3], T1[1][3], T1[2][3]);
//	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Сделать вычисление нормалей к поверхности!!!
	//Polygons[i].normal.x = v1.y*v2.z - v2.y*v1.z;
	//Polygons[i].normal.y = v2.x*v1.z - v1.x*v2.z;
	//Polygons[i].normal.z = v1.x*v2.y - v1.y*v2.x;
	for (i = 0; i < 1; i++)
	{
		//getting coords for normals calculating...
		x1 = vertexes[vSequence[4 * i + 2]].xyz[(ax + 1) % 3] - vertexes[vSequence[4 * i + 3]].xyz[(ax + 1) % 3];
		x2 = vertexes[vSequence[4 * i]].xyz[(ax + 1) % 3] - vertexes[vSequence[4 * i + 3]].xyz[(ax + 1) % 3];
		y1 = vertexes[vSequence[4 * i + 2]].xyz[(ax + 2) % 3] - vertexes[vSequence[4 * i + 3]].xyz[(ax + 2) % 3];
		y2 = vertexes[vSequence[4 * i]].xyz[(ax + 1) % 3] - vertexes[vSequence[4 * i + 3]].xyz[(ax + 1) % 3];
		z1 = vertexes[vSequence[4 * i + 2]].xyz[ax] - vertexes[vSequence[4 * i + 3]].xyz[ax];
		z2 = vertexes[vSequence[4 * i]].xyz[ax] - vertexes[vSequence[4 * i + 3]].xyz[ax];
		glBegin(GL_LINES);
			glColor3d(1, 0, 0);
			glVertex3dv(vertexes[vSequence[4*i]].xyz);
			glVertex3d(vertexes[vSequence[4 * i]].xyz[0] + (y1*z2 - y2*z1), 
				vertexes[vSequence[4 * i]].xyz[1] + (x2*z1 - x1*x2), 
				vertexes[vSequence[4 * i]].xyz[2]+(x1*y2 - x2*y1));
		glEnd();
		glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		glNormal3d(y1*z2-y2*z1, x2*z1-x1*x2, x1*y2-x2*y1);
		for (j = 0; j < 4; j++)
		{
			glVertex3dv(vertexes[vSequence[4*i+j]].xyz);
		}
		glEnd();
	}
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
