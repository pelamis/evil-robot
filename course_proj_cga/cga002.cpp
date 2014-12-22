#include "KPairArray.h"
#include "KinematicPair.h"
#include "Light.h"
#include "Link.h"
#include "Camera.h"
#include <random>
#include <time.h>
#include "callbacks.h"

#define dl cos(M_PI_4)

GLint pMode=GL_LINE; 
GLdouble A = SCREEN_WIDTH / 4.0, B = 0.0, C = SCREEN_HEIGHT / 2.0, D = C;

KPairArray *KPArray2;
Link *linkArray;
Camera *camera;
Light *l0;


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
	//l0->Enable();
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
		linkArray[i].reGetT0(T0);
		linkArray[i].buildMesh();
		linkArray[i].drawLink();
	}
	//glEnable(GL_NORMALIZE);
	//l0->Enable();
	for (i = 0; i < len; i++) KPArray2->getPair(i).moveKP();	
}

int main(int argc, _TCHAR* argv[])
{
	int i, k;
	init();
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

void init()
{
	int i;
	GLdouble lenSequence[KP_NUMBER] = {D1,-A1-50,A1,50,50,0};
	GLdouble axisSequense[KP_NUMBER][3] = { {0,0,1}, {1,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1} };
	//сделать так, чтобы смещение меняло точку "начала" звена
	GLdouble offsetSequense[KP_NUMBER][3] = { { 100 * dl, 0, 25 * dl }, { 50, 0, 35 }, { 25, 70, -50 }, { 0, 25, 50 }, { 0, 75, 0 }, { 0, 0, 0 } };
	GLdouble sidesSequense[KP_NUMBER][2] = { { 50, 50 }, { 50, 25 }, { 50, 25 }, { 50, 50 }, { 50, 50 }, { 10, 10 } };

	l0 = new Light();
	KPArray2 = new KPairArray();
	camera = new Camera();
	linkArray = new Link[KP_NUMBER];
	for (i = 0; i < KP_NUMBER - 1; i++) linkArray[i].reInit(NULL, axisSequense[i], offsetSequense[i], sidesSequense[i][0], sidesSequense[i][1], lenSequence[i]);
}

// saves the result in m1
void mul(GLdouble ** m1, GLdouble ** m2)
{
	int i, j, k;

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