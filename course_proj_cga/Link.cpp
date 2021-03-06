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
	this->polygons = new Polygon*[6];
	for (i = 0; i < 6; i++) polygons[i] = NULL;
	this->side1 = side1;
	this->side2 = side2;
	this->len = len;
}


Link::~Link()
{
	int i;
	delete vertexes;
	delete axis;
	delete offset;
	for (i = 0; i < 6; i++) delete polygons[i];
	delete polygons;
}

//BEWARE OF MORONS!!!
void Link::buildMesh()
{
	int i,j;
	int coords[4][2] = { { side1/2, -side2/2 }, { side1/2, side2/2}, 
						{ -side1/2, side2/2 }, { -side1/2, -side2/2 } };
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
	for (i = 0; i < 6; i++)
	{
		if (polygons[i]==NULL)
			polygons[i] = new Polygon(&vertexes[vSequence[4 * i]], &vertexes[vSequence[4 * i + 1]],
									  &vertexes[vSequence[4 * i + 2]], &vertexes[vSequence[4 * i + 3]],axis[0],axis[1],axis[2]);
		polygons[i]->getNormal();
	}
	glLineWidth(1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for (i = 0; i < 6; i++)
	{
		polygons[i]->drawPolygon();
		//polygons[i]->drawNormal();
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
