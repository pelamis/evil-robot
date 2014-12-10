#pragma once

#ifndef LIGHT_H
#define LIGHT_H_

#include "commons.h"

class Light {
public:
	GLfloat *RGB,
		*normal,
		*position,
		*amb,
		*diff,
		*spec,
		*spdir,
		exp, cutoff, kc, kl, kq;

	char e = 0;

	Light(GLfloat *color, GLfloat *n, GLfloat *pos, GLfloat *a, GLfloat *d, GLfloat *s, GLfloat *sdir,
		GLfloat e, GLfloat coff, GLfloat k_c, GLfloat k_l, GLfloat k_q);
	void SetColor(GLfloat *color);
	void SetGeom(GLfloat *n, GLfloat *pos, GLfloat *sdir, GLfloat e, GLfloat coff);
	void SetLightConf(GLfloat *a, GLfloat *d, GLfloat *s, GLfloat k_c, GLfloat k_l, GLfloat k_q);
	void Enable();
	void Disable();
};

#endif
