#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include "commons.h"
#include "KPairArray.h"

void movef(GLfloat mov_x, GLfloat mov_y, GLfloat mov_z);
void turnf(GLfloat tr_x, GLfloat tr_y, GLfloat tr_z, GLfloat angle, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z);
void cursor_callback(GLFWwindow* window, double x, double y);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void resize_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error_callback(int error, const char* description);

#endif