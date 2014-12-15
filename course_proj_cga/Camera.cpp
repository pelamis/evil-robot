#include "Camera.h"


Camera::Camera()
{
	degPhi = 90;
	degTheta = 90;
	eyex = 0;
	eyey = 0;
	eyez = -330;
	cntx = 0;
	cnty = sin(DEG_TO_RAD*degTheta)*sin(DEG_TO_RAD*degPhi);
	cntz = 0;
	upvx = 0;
	upvy = 0;
	upvz = 1;
}

void Camera::setCameraPos(GLdouble ex, GLdouble ey, GLdouble ez,
	GLdouble degPhi, GLdouble degTheta,
	GLdouble ux, GLdouble uy, GLdouble uz)
{
	eyex = ex;
	eyey = ey;
	eyez = ez;
	cntx = sin(DEG_TO_RAD*degTheta)*cos(DEG_TO_RAD*degPhi);
	cnty = sin(DEG_TO_RAD*degTheta)*sin(DEG_TO_RAD*degPhi);
	cntz = cos(DEG_TO_RAD*degTheta);
	upvx = ux;
	upvy = uy;
	upvz = uz;
	
}

void Camera::rotateCam(GLdouble phi, GLdouble theta)
{
	GLdouble radPhi,radTheta;
	if (degPhi+phi<360) degPhi += phi;
	else degPhi = degPhi + phi - 360;
	if (degTheta + theta<360) degTheta += theta;
	else degTheta = degTheta + theta - 360;

	radTheta = DEG_TO_RAD*degTheta;
	radPhi = DEG_TO_RAD*degPhi;
	cntx = sin(DEG_TO_RAD*degTheta)*cos(DEG_TO_RAD*degPhi);
	cnty = sin(DEG_TO_RAD*degTheta)*sin(DEG_TO_RAD*degPhi);
	cntz = cos(DEG_TO_RAD*degTheta);
}

Camera::~Camera()
{
}
