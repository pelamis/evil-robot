#include "commons.h"
#include "stdafx.h"
#include <random>
#include "stdafx.h"
#include <time.h>

GLdouble /*PROJ_ANGLE=45*M_PI/180,*/t=0;

GLdouble SPEED = M_PI / 100000;
GLdouble SPEED2 = M_PI / 10000;
GLint pMode=GL_LINE; 
GLint flag[5] = {0,0,0,0,0};

KP KPArray[KP_NUMBER];

Light l0(lcolr0, n0, pos0, a0, d0, s0, sd0, 0, M_PI, 1, 1, 1);

static void cursor_callback(GLFWwindow* window, double x, double y)
{
	
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS) glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if(action == GLFW_RELEASE) glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

static void resize_callback(GLFWwindow* window, int width, int height)
{
	int pcside;
	pcside=(width>height?width:height)*2;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0.0, width, 0.0, height, -pcside, pcside);
	gluLookAt(0, 0, 0, 0, 1, 0, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	A = width / 4.0;
	B = 0.0;
	C = D = height / 2.0;
	printf("Reshape occured\n");
}

static void movef(GLfloat mov_x, GLfloat mov_y, GLfloat mov_z)
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(mov_x, mov_y, mov_z);
	printf("You moved\n");
}

static void turnf(GLfloat tr_x, GLfloat tr_y, GLfloat tr_z, GLfloat angle, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z)
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(tr_x, tr_y, tr_z);
	glRotatef(angle, rot_x, rot_y, rot_z);
	glTranslatef(-tr_x, -tr_y, -tr_z);
	printf("Turn occured\n");
}

static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_LEFT)
	{
		turnf(A * 2, C, 0.5, -M_PI / 4, 0, 0, SPEED);
	}
	if (key == GLFW_KEY_RIGHT)
	{
		turnf(A * 2, C, 0.5, M_PI / 4, 0, 0, SPEED);
	}

	if (key == GLFW_KEY_Z)
	{
		turnf(A * 2, C, 0.5, M_PI / 4, SPEED, 0, 0);
	}

	if (key == GLFW_KEY_X)
	{
		turnf(A * 2, C, 0.5, -M_PI / 4, SPEED, 0, 0); //реализовать через gluLookAt!!!
	}
	if (key == GLFW_KEY_UP)
	{
			movef(0, 10, 0);
	}

	if (key == GLFW_KEY_DOWN)
	{
		movef(0, -10, 0);
	}
	if ((key == GLFW_KEY_1)&&(action==GLFW_PRESS))
	{
		flag[0] = (flag[0] == 0);
	}
	if ((key == GLFW_KEY_2)&&(action==GLFW_PRESS))
	{
		flag[1] = (flag[1] == 0);
	}
	if ((key == GLFW_KEY_3)&&(action==GLFW_PRESS))
	{
		flag[2] = (flag[2] == 0);
	}
	if ((key == GLFW_KEY_4)&&(action==GLFW_PRESS))
	{
		flag[3] = (flag[3] == 0);
	}

	if ((key == GLFW_KEY_5) && (action == GLFW_PRESS))
	{
		flag[4] = (flag[4] == 0);
	}

	if ((key == GLFW_KEY_6) && (action == GLFW_PRESS))
	{
		flag[5] = (flag[5] == 0);
	}

}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void move(KP *nodeArray)
{
	char i;

	for (i = 0; i < KP_NUMBER; i++)
	{
		if (nodeArray[i].q >= MAXANGLE) SPEED2 = -SPEED2;
		if (nodeArray[i].q <= -MAXANGLE) SPEED2 = abs(SPEED2);
		if (flag[i]) nodeArray[i].q += SPEED2;
		
	}
	buildAMatr(nodeArray);
	//опросить все пары
	//изменить q
}

void draw()
{
	GLdouble side=(A<C?A:C)/2;
	l0.Enable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//resize here
	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(A, 0, C/10);
	glPopMatrix();
// draw here
	drawBackground();
	drawAxis();
	drawKP(KPArray);
	move(KPArray);	
}

int main(int argc, _TCHAR* argv[])
{
	int i, k;
	init(KPArray);
	// initialise GLFW
    if(!glfwInit())
	{
		printf("glfwInit failed\n");
		return -1;
	}

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window;
	
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test app", NULL, NULL);
	if (window == NULL)
	{
		printf("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?\n");
		glfwTerminate();
		return -2;
	}

	int attrib;
	attrib = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
	attrib = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
	attrib = glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	
    resize_callback(window, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	while (!glfwWindowShouldClose(window))
	{
		draw();

		glfwSwapBuffers(window);
		
		glfwPollEvents();
		//glfwWaitEvents();
	}

	glfwDestroyWindow(window);

	// clean up and exit
	for (k = 0; k < KP_NUMBER;k++)
		for (i = 0; i < 4; i++) delete KPArray[k].A[i];
		delete KPArray[k].A;
    glfwTerminate();

	return 0;
}
//=============================================================


void drawAxis()
{
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(10, 10, 10);
	glVertex3d(110, 10, 10);
	glColor3d(0, 1, 0);
	glVertex3d(10, 10, 10);
	glVertex3d(10, 110, 10);
	glColor3d(0, 0, 1);
	glVertex3d(10, 10, 10);
	glVertex3d(10, 10, 110);
	glEnd();
}

void drawBackground()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3d(0.5, 0.5, 0.5);
	glVertex3d(0,0,5);
	glVertex3d(0, A * 4, 5);
	glVertex3d(A*4,A*4,5);
	glVertex3d(A * 4, 0, 5);
	glEnd();
}

void drawKP(KP *nodeArray)
{
	char i,j;
	GLdouble** T = new PGLdouble[4];
	for (i = 0; i < 4; i++) T[i] = new GLdouble[4];
	setMatr(T, nodeArray[0].A, 4);
	glLineWidth(5);
	glBegin(GL_LINES);
	//mul(T, nodeArray[1].A);
		for (i = 1; i < KP_NUMBER-1; i++)
		{
			glColor3d(1, 1, 0);
			glVertex3d(T[0][3], T[1][3], T[2][3]);
			mul(T, nodeArray[i+1].A);
			glColor3d(1, 0, 0);
			glVertex3d(T[0][3], T[1][3], T[2][3]);
		}
	glEnd();
	glLineWidth(2);
	for (i = 0; i < 4; i++) delete T[i];
	delete T;
}

void init(KP *nodeArray)
{
	char i,j,k;
	for (i = 0; i < KP_NUMBER; i++)
	{
		nodeArray[i].a = 0;
		nodeArray[i].d = 0;
		nodeArray[i].q = 0;
		nodeArray[i].alpha = 0;

		nodeArray[i].A=new PGLdouble[4];
		for (j = 0; j < 4; j++) nodeArray[i].A[j] = new GLdouble[4];
	}

	for (i = 0; i < KP_NUMBER;i++)
	for (j = 0; j < 4; j++)
	for (k = 0; k < 4;k++)
	{
		nodeArray[i].A[j][k] = 0;
	}

	nodeArray[0].alpha = -(M_PI / 2);
	nodeArray[0].q = M_PI / 2;

	nodeArray[1].d = D1;
	nodeArray[1].a = A1;

	nodeArray[2].a = A2;
	nodeArray[2].alpha = M_PI / 2;
	nodeArray[2].q = M_PI / 2;

	nodeArray[3].d = D3;
	nodeArray[3].alpha = -(M_PI / 2);

	nodeArray[4].alpha = M_PI / 2;
	
	nodeArray[5].d = D5;
	
	buildAMatr(nodeArray);
}

// saves the result in m1
void mul(GLdouble ** m1, GLdouble ** m2)
{
	int i, j, k;
	//for (i = 0; i < 4; i++)
	//{
	//	for (j = 0; j < 4; j++)
	//	{
	//		printf_s("%lf\t", m1[i][j]);
	//	}
	//	printf_s("\n");
	//}
	//printf_s("\n\n");
	//for (i = 0; i < 4; i++)
	//{
	//	for (j = 0; j < 4; j++)
	//	{
	//		printf_s("%lf\t", m2[i][j]);
	//	}
	//	printf_s("\n\n");
	//}

	GLdouble **res = new PGLdouble[4];
	for (i = 0; i < 4; i++) res[i] = new GLdouble[4];
	for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++) res[i][j] = 0;

	for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	for (k = 0; k < 4;k++)
	{
		res[i][j] += m1[i][k] * m2[k][j];
	}
	setMatr(m1, res, 4);
	//for (i = 0; i < 4; i++)
	//{
	//	for (j = 0; j < 4; j++)
	//	{
	//		printf_s("%lf\t", m1[i][j]);
	//	}
	//	printf_s("\n");
	//}
	//printf_s("\n\n");
	for (i = 0; i < 4; i++) delete res[i];
	delete res;
	return;
}

void buildAMatr(KP *nodeArray)
{
	int i, j;
	GLdouble s , c, ac, as, a, d;

	for (i = 0; i < KP_NUMBER; i++)
	{
		s = sin(nodeArray[i].q);
		c = cos(nodeArray[i].q);
		as = sin(nodeArray[i].alpha);
		ac = cos(nodeArray[i].alpha);
		a = nodeArray[i].a;
		d = nodeArray[i].d;

		nodeArray[i].A[0][0]=c;
		nodeArray[i].A[1][0] = s;
		nodeArray[i].A[0][1] = -ac*s;
		nodeArray[i].A[1][1] = ac*c;
		nodeArray[i].A[0][2] = as*s;
		nodeArray[i].A[1][2] = -as*c;
		nodeArray[i].A[2][1] = as;
		nodeArray[i].A[2][2] = ac;
		nodeArray[i].A[0][3] = a*c;
		nodeArray[i].A[1][3] = a*s;
		nodeArray[i].A[2][3] = d;
		nodeArray[i].A[3][3] = 1;
	}
}

void setMatr(GLdouble ** dst, GLdouble ** src, int ord)
{
	int i, j;
	for (i = 0; i < ord;i++)
	for (j = 0; j < ord; j++) dst[i][j] = src[i][j];
}

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