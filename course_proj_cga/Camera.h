#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "commons.h"
class Camera
{
public:

	GLdouble	eyex, eyey, eyez,
		cntx, cnty, cntz,
		upvx, upvy, upvz;
	//in degrees!
	GLdouble degPhi, degTheta;

	Camera();
	void setCameraPos(GLdouble ex, GLdouble ey, GLdouble ez,
		GLdouble degPhi, GLdouble degTheta,
		GLdouble ux, GLdouble uy, GLdouble uz);
	void rotateCam(GLdouble phi, GLdouble theta);
	~Camera();
};
#endif

