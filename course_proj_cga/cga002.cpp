// cga002.cpp: определ€ет точку входа дл€ консольного приложени€.
//2€ лаба: вз€ть куб, получить матрицу преобр, применить преобр-ние, вывести. Ќарисовать 2й куб, анимированный.
// онус: основание - концентрические окружности, контур - не линии, а "плитки".
//13-й вар.
//  http://www.glfw.org/docs/latest/quick.html
#include "commons.h"
#include "stdafx.h"
#include <random>
#include "stdafx.h"
#include <time.h>

GLdouble PROJ_ANGLE=45*M_PI/180,t=0;

GLdouble orth[16]={1,0,0,0, 0,1,0,0, -cos(PROJ_ANGLE),-sin(PROJ_ANGLE),1,0, 0,0,0,1};
GLdouble SPEED = M_PI / 100000;
GLint pMode=GL_LINE; 
GLdouble cyan[3]={0,1,1};

KP KPArray[5];

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
		turnf(A * 2, C, 0.5, -M_PI / 4, 0, SPEED, 0);
	}
	if (key == GLFW_KEY_RIGHT)
	{
		turnf(A * 2, C, 0.5, M_PI / 4, 0, SPEED, 0);
	}
		if (key == GLFW_KEY_UP)
	{
			turnf(A * 2, C, 0.5, M_PI / 4, 0, 0, SPEED);
	}

	if (key == GLFW_KEY_DOWN)
	{
		turnf(A * 2, C, 0.5, -M_PI / 4, 0, 0, SPEED);
	}
	if ((key == GLFW_KEY_W)&&(action==GLFW_PRESS))
	{
	
	}
	if ((key == GLFW_KEY_S)&&(action==GLFW_PRESS))
	{
	
	}
	if ((key == GLFW_KEY_D)&&(action==GLFW_PRESS))
	{
		
	}
	if ((key == GLFW_KEY_A)&&(action==GLFW_PRESS))
	{
		
	}
	if ((key == GLFW_KEY_M)&&(action==GLFW_PRESS))
	{
		
	}
}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void move(KP *nodeArray)
{
	char i;

	for (i = 1; i < KP_NUMBER; i++)
	{
		if (nodeArray[i].q >= MAXANGLE) SPEED = -SPEED;
		if (nodeArray[i].q <= -MAXANGLE) SPEED = abs(SPEED);
		nodeArray[i].q += SPEED;
		buildAMatr(&(nodeArray[i]), i);
	}

	//опросить все пары
	//изменить q
	//перестроить —  ƒ-’ дл€ всех затронутых узлов
}

void draw()
{
	GLdouble side=(A<C?A:C)/2;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//resize here
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
// draw here
	drawAxis();
	drawKP(KPArray);
	//movedbg();
	move(KPArray);	
}

int main(int argc, _TCHAR* argv[])
{

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
 //матрица: строки матрицы - столбцы, 1-й столбец - 1-€ строка матрицы в пам€ти
void drawKP(KP *nodeArray)
{
	char i,j;
	GLdouble** T = new PGLdouble[4];
	for (i = 0; i < 4; i++) T[i] = new GLdouble[4];
	setMatr(T, nodeArray[0].A, 4);
	glBegin(GL_LINE_STRIP);
		for (i = 1; i < KP_NUMBER; i++)
		{
			mul(T, nodeArray[i].A);
			glColor3d(1, 1, 0);
			glVertex3d(T[0][3], T[1][3], T[2][3]);
		}
	glEnd();
	for (i = 0; i < 4; i++) delete T[i];
	delete T;
}

void init(KP *nodeArray)
{
	GLdouble **identity=new PGLdouble[4];
	char i, j, k;

	for (i = 0; i < 4; i++)
	{
		identity[i] = new GLdouble[4];
		for (j = 0; j < 4; j++) identity[i][j] = (i == j);
	}

	for (i = 0; i < KP_NUMBER; i++)
	{
		nodeArray[i].a = 0;
		nodeArray[i].alpha = 0;
		nodeArray[i].d = 0;
		nodeArray[i].q = 0;

		nodeArray[i].A=new PGLdouble[4];
		for (j = 0; j < 4; j++) nodeArray[i].A[j] = new GLdouble[4];
	}
	setMatr(nodeArray[0].A, identity, 4);
	for (i = 1; i < KP_NUMBER; i++) buildAMatr(&(nodeArray[i]), i);

	for (i = 0; i < 4; i++) delete identity[i];
	delete identity;
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
	}
	setMatr(m1, res, 4);
	for (i = 0; i < 4; i++) delete res[i];
	delete res;
	return;
}

void buildAMatr(KP *KPair,int kpnum)
{
	int i, j;
	for (i = 0; i < 4;i++)
	for (j = 0; j < 4; j++) KPair->A[i][j] = 0;

	if (kpnum == 1) 
	{
		KPair->A[0][3] = A*2;
	//	KPair->A[1][3] = ;
		KPair->A[2][3] = C/10 ;
	}
	KPair->A[3][3] = 1;
	KPair->A[0][0] = cos(KPair->q);
	KPair->A[1][0] = sin(KPair->q);

	if (kpnum != 2)
	{
		KPair->A[0][1] = -sin(KPair->q);
		KPair->A[1][1] = cos(KPair->q);
		KPair->A[2][2] = 1;
		if (kpnum == 3 || kpnum == 4) KPair->A[0][3] = LEN1*cos(KPair->q);
	}
	else
	{
		KPair->A[0][2] = sin(KPair->q);
		KPair->A[1][2] = -cos(KPair->q);
		KPair->A[2][1] = 1;
		KPair->A[2][3] = LEN1;
	}
}

void setMatr(GLdouble ** dst, GLdouble ** src, int ord)
{
	int i, j;
	for (i = 0; i < ord;i++)
	for (j = 0; j < ord; j++) dst[i][j] = src[i][j];
}

