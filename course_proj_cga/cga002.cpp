#include "KPairArray.h"
#include "KinematicPair.h"
#include "Light.h"
#include "Link.h"
#include "Camera.h"
#include <random>
#include <time.h>
#include "callbacks.h"

//GLdouble SPEED = M_PI / 100000;
//GLdouble SPEED2 = M_PI / 10000;
GLint pMode=GL_LINE; 
GLdouble A = SCREEN_WIDTH / 4.0, B = 0.0, C = SCREEN_HEIGHT / 2.0, D = C;
GLfloat lcolr0[3] = { 1, 1, 1 },
n0[3] = { 1, 1, 0 },
pos0[4] = { 10, 10, 10, 0 },
a0[4] = { 0.2, 0.2, 0.2, 1 },
d0[4] = { 1, 1, 1, 1 },
s0[4] = { 1, 1, 1, 1 },
sd0[3] = { 0, 0, -1 };

KPairArray *KPArray2;
Link *linkArray;
Camera *camera;

Light l0(lcolr0, n0, pos0, a0, d0, s0, sd0, 0, M_PI, 1, 1, 1);

//callbacks here

void movef(GLfloat mov_x, GLfloat mov_y, GLfloat mov_z)
{
	glMatrixMode(GL_MODELVIEW);
	//glTranslatef(mov_x, mov_y, mov_z);
	//gluLookAt(mov_x)
	printf("You moved\n");
}

void turnf(GLfloat tr_x, GLfloat tr_y, GLfloat tr_z, GLfloat angle, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z)
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(tr_x, tr_y, tr_z);
	glRotatef(angle, rot_x, rot_y, rot_z);
	glTranslatef(-tr_x, -tr_y, -tr_z);
	printf("Turn occured\n");
}

void draw()
{
	int i,j,k,len;
	GLdouble side = (A<C ? A : C) / 2;
	GLdouble **T0 = NULL, **T1 = NULL;
	//l0.Enable();
	//l0.Disable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//resize here
	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(A, 0, C/10);
	glPopMatrix();
// draw here

	//drawBackground();
	drawAxis();
	len = KPArray2->getLength();	
	for (i = 0; i < len; i++) KPArray2->drawPair(i);
	for (i = 0; i < KP_NUMBER - 1; i++)
	{
		T0 = KPArray2->getTForPair(i);
		//T1 = KPArray2->getTForPair(i + 1);
		linkArray[i].reGetT0(T0);
		linkArray[i].buildMesh();
		linkArray[i].drawLink();
	}
	//l0.Enable();
	for (i = 0; i < len; i++) KPArray2->getPair(i).moveKP();	
}

int main(int argc, _TCHAR* argv[])
{
	int i, k;
	KPArray2 = new KPairArray();
	camera = new Camera();
	linkArray = new Link[KP_NUMBER];
	for (i = 0; i < KP_NUMBER - 1; i++) linkArray[i].reInit(NULL,0,0,1,50,50);
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
	
    glfwTerminate();
	return 0;
}
//=============================================================


void drawAxis()
{
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 1);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 1);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 100);
	glEnd();
}

void drawBackground()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3d(0.5, 0.5, 0.5);
	glVertex3d(-A * 2, 0, -660.4);
	glVertex3d(-A * 2, A * 2, -660.4);
	glVertex3d(A * 2, A * 2, -660.4);
	glVertex3d(A * 2, 0, -660.4);
	glEnd();
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
		if (abs(res[i][j]) < pow(10,-15)) res[i][j] = 0;
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

void setMatr(GLdouble ** dst, GLdouble ** src, int ord)
{
	int i, j;
	for (i = 0; i < ord;i++)
	for (j = 0; j < ord; j++) dst[i][j] = src[i][j];
}

//