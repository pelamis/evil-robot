#include "Light.h"


GLfloat ma[4] = { 0.2, 0.5, 0.5, 1 };
GLfloat md[4] = { 0.2, 0.2, 0.8, 1 };
GLfloat ms[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shine[1] = { 63 };
GLfloat ascene[4] = { 0, 0.5, 0.5, 1 };

Light::Light(GLfloat *color, GLfloat *n, GLfloat *pos, GLfloat *a, GLfloat *d, GLfloat *s, GLfloat *sdir,
		GLfloat e, GLfloat coff, GLfloat k_c, GLfloat k_l, GLfloat k_q) {
		RGB = color;
	
		normal = n;
		position = pos;
		spdir = sdir;
		cutoff = coff;
		exp = e;
	
		amb = a;
		diff = d;
		spec = s;
		kc = k_c;
		kl = k_l;
		kq = k_q;
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
		glMaterialfv(GL_FRONT, GL_AMBIENT, ma);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, md);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms);
		glMaterialfv(GL_FRONT, GL_SHININESS, shine);
		glColor3fv(RGB);
		glEnable(GL_NORMALIZE);
	
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
	
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
		glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &kc);
		glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &kl);
		glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &kq);
	
		glLightModelfv(GL_AMBIENT, ascene);
	}
