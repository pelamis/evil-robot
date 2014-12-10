#include "KPairArray.h"
#include "KinematicPair.h"
#include "Light.h"
#include <random>
#include <time.h>

GLdouble SPEED = M_PI / 100000;
GLdouble SPEED2 = M_PI / 10000;
GLint pMode=GL_LINE; 
GLint flag[5] = {0,0,0,0,0};
GLdouble PI = M_PI;
GLdouble A = SCREEN_WIDTH / 4.0, B = 0.0, C = SCREEN_HEIGHT / 2.0, D = C;
GLfloat lcolr0[3] = { 1, 1, 1 },
n0[3] = { 1, 1, 0 },
pos0[4] = { 10, 10, 10, 0 },
a0[4] = { 0.2, 0.2, 0.2, 1 },
d0[4] = { 1, 1, 1, 1 },
s0[4] = { 1, 1, 1, 1 },
sd0[3] = { 0, 0, -1 };

KPairArray *KPArray2;

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
		turnf(A * 2, C, 0.5, -M_PI / 4, SPEED, 0, 0); //����������� ����� gluLookAt!!!
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
		KPArray2[0].moveSwitch();
	}
	if ((key == GLFW_KEY_2)&&(action==GLFW_PRESS))
	{
		KPArray2[1].moveSwitch();
	}
	if ((key == GLFW_KEY_3)&&(action==GLFW_PRESS))
	{
		KPArray2[2].moveSwitch();
	}
	if ((key == GLFW_KEY_4)&&(action==GLFW_PRESS))
	{
		KPArray2[3].moveSwitch();
	}

	if ((key == GLFW_KEY_5) && (action == GLFW_PRESS))
	{
		KPArray2[4].moveSwitch();
	}

	if ((key == GLFW_KEY_6) && (action == GLFW_PRESS))
	{
		KPArray2[5].moveSwitch();
	}

}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void drawKP2()
{
	char i, j;
	GLdouble** T = new PGLdouble[4];
	//for (i = 0; i < 4; i++) T[i] = new GLdouble[4];
	//for (i = 0; i < 4; i++)
	//for (j = 0; j < 4; j++) T[i][j] = (i == j);

	glPointSize(10.0);
	for (i = 0; i < KP_NUMBER; i++)
	{
		//glColor3d(1, 1, 0);
		//glVertex3d(T[0][3], T[1][3], T[2][3]);
	//	mul(T, KPArray2[i].A);
		
		glBegin(GL_POINTS);
		glColor3d(0, 1, 1);
		glVertex3d(T[0][3], T[1][3], T[2][3]);
		glEnd();
		
	}
	for (i = 0; i < 4; i++) delete T[i];
	delete T;

}

void draw()
{
	int i;
	GLdouble side=(A<C?A:C)/2;
//	l0.Enable();
	//l0.Disable();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//resize here
	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(A, 0, C/10);
	glPopMatrix();
// draw here

	drawBackground();
	drawAxis();

	//drawKP(KPArray);
	drawKP2();
	for (i = 0; i < KP_NUMBER; i++) KPArray2[i].moveKP();
	//move(KPArray);	
}

KinematicPair * init()
{
	KinematicPair *KPArray2 = new KinematicPair[KP_NUMBER];
	int i;
	GLdouble a_init[KP_NUMBER]		= { 0, A1, A2, 0, 0, 0 };
	GLdouble q_init[KP_NUMBER]		= { M_PI_2, 0, M_PI_2, 0, 0, 0 };
	GLdouble d_init[KP_NUMBER]		= { 0, D1, 0, D3, 0, D5 };
	GLdouble alpha_init[KP_NUMBER]	= { -M_PI_2, 0, M_PI_2, -M_PI_2, M_PI_2, 0 };
	GLdouble minq_init[KP_NUMBER]	= { -160, -225, -45, -110, -100, -266 };
	GLdouble maxq_init[KP_NUMBER]	= { 160, 45, 225, 170, 100, 266 };
	for (i = 0; i < KP_NUMBER; i++) KPArray2[i].reInit(a_init[i],q_init[i],d_init[i],alpha_init[i],DEG_TO_RAD*minq_init[i],DEG_TO_RAD*maxq_init[i]);
	return KPArray2;
}

int main(int argc, _TCHAR* argv[])
{
	int i, k;
	KPArray2 = init();
	
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

void setMatr(GLdouble ** dst, GLdouble ** src, int ord)
{
	int i, j;
	for (i = 0; i < ord;i++)
	for (j = 0; j < ord; j++) dst[i][j] = src[i][j];
}

//