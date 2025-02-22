#ifndef OPENGL_H
#define OPENGL_H

#include "GLFW/glfw3.h"
#include <iostream>

void gl_draw_circle(int xC, int yC, int r, int t);
void gl_draw_filled_circle(int xC, int yC, int r);
void render_text(std::string text, float x, float y);

void drawCube();
GLFWwindow* init_opengl(int resolution_x, int resolution_y);

#endif
