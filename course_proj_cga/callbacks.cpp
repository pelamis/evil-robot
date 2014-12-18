#include "callbacks.h"

extern GLdouble A, B, C, D;
extern KPairArray *KPArray2;

void cursor_callback(GLFWwindow* window, double x, double y)
{

}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (action == GLFW_RELEASE) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void resize_callback(GLFWwindow* window, int width, int height)
{
	int pcside;
	pcside = (width>height ? width : height) * 2;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width, width, -height, height, -pcside * 10, pcside * 10);
	gluLookAt(0, -300, 0, 1, 1, 1, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	A = width / 4.0;
	B = 0.0;
	C = D = height / 2.0;
	printf("Reshape occured\n");
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if ((key == GLFW_KEY_LEFT) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		turnf(A * 2, C, 0.5, -M_PI / 4, 0, 0, SPEED);
		//		camera->rotateCam(-1, 0);
		//gluLookAt(camera->eyex, camera->eyey, camera->eyez, 
		//	camera->cntx, camera->cnty, camera->cntz, 
		//	camera->upvx, camera->upvy, camera->upvz);
	}
	if ((key == GLFW_KEY_RIGHT) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		turnf(A * 2, C, 0.5, M_PI / 4, 0, 0, SPEED);
		//camera->rotateCam(1, 0);
		/*gluLookAt(camera->eyex, camera->eyey, camera->eyez,
		camera->cntx, camera->cnty, camera->cntz,
		camera->upvx, camera->upvy, camera->upvz);*/
	}

	if ((key == GLFW_KEY_Z) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		turnf(A * 2, C, 0.5, M_PI / 4, SPEED, 0, 0);
		/*camera->rotateCam(0, -1);
		gluLookAt(camera->eyex, camera->eyey, camera->eyez,
		camera->cntx, camera->cnty, camera->cntz,
		camera->upvx, camera->upvy, camera->upvz);*/
	}

	if ((key == GLFW_KEY_X) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		turnf(A * 2, C, 0.5, -M_PI / 4, SPEED, 0, 0); //реализовать через gluLookAt!!!
		/*camera->rotateCam(0, 1);
		gluLookAt(camera->eyex, camera->eyey, camera->eyez,
		camera->cntx, camera->cnty, camera->cntz,
		camera->upvx, camera->upvy, camera->upvz);*/
	}
	if (key == GLFW_KEY_UP && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		movef(0, 10, 0);
	}
	if (key == GLFW_KEY_DOWN && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
	{
		movef(0, -10, 0);
	}
	if ((key == GLFW_KEY_1) && (action == GLFW_PRESS))
	{
		KPArray2->getPair(0).moveSwitch();
	}
	if ((key == GLFW_KEY_2) && (action == GLFW_PRESS))
	{
		KPArray2->getPair(1).moveSwitch();
	}
	if ((key == GLFW_KEY_3) && (action == GLFW_PRESS))
	{
		KPArray2->getPair(2).moveSwitch();
	}
	if ((key == GLFW_KEY_4) && (action == GLFW_PRESS))
	{
		KPArray2->getPair(3).moveSwitch();
	}
	if ((key == GLFW_KEY_5) && (action == GLFW_PRESS))
	{
		KPArray2->getPair(4).moveSwitch();
	}
	if ((key == GLFW_KEY_6) && (action == GLFW_PRESS))
	{
		KPArray2->getPair(5).moveSwitch();
	}

}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}