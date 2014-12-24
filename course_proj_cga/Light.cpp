#include "Light.h"

Light::Light() {
		
		GLfloat lcolr0[3] = { 1, 1, 1 },
		n0[3] = { 0, 0, -1 },
		pos0[4] = { -1, 0, -1, 0 },
		a0[4] = { 0.5, 0.5, 0.5, 1 },
		d0[4] = { 0.7, 0.7, 0.7, 1 },
		s0[4] = { 1, 1, 1, 1 },
		sd0[3] = { 0, 0, -1 };
		
		RGB = lcolr0;
	
		normal = n0;
		position = pos0;
		spdir = sd0;
		cutoff = 30;
		exp = M_PI;
	
		amb = a0;
		diff = d0;
		spec = s0;
		kc = 1;
		kl = 1;
		kq = 1;
	}
	
	void Light::SetColor(GLfloat *color) {
		RGB = color;
	}
	
	void Light::SetGeom(GLfloat *n, GLfloat *pos, GLfloat *sdir, GLfloat e, GLfloat coff) {
		normal = n;
		position = pos;
		spdir = sdir;
		cutoff = coff;
		exp = e;
	}
	
	void Light::SetLightConf(GLfloat *a, GLfloat *d, GLfloat *s, GLfloat k_c, GLfloat k_l, GLfloat k_q) {
		amb = a;
		diff = d;
		spec = s;
		kc = k_c;
		kl = k_l;
		kq = k_q;
	}
	
	void Light::Enable() {

		GLfloat ma[4] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat md[4] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat ms[4] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shine[1] = { 0.5 };
		GLfloat ascene[4] = {0.2, 0.2, 0.2, 1};

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ma);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, md);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
		glColor3fv(RGB);
	//	glEnable(GL_NORMALIZE);
	
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		//glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
	
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	//	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &kc);
	//	glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &kl);
	//	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &kq);
	
		glLightModelfv(GL_AMBIENT, ascene);

		glEnable(GL_LIGHTING);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
	}

	void Light::Disable() {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
	}
