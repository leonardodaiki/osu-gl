#ifndef OPENGL_H
#define OPENGL_H

#include "GLFW/glfw3.h"

void gl_draw_circle(int xC, int yC, int r);

GLFWwindow* init_opengl(int resolution_x, int resolution_y);

#endif
