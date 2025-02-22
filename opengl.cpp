#include <GL/freeglut_std.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "opengl.hpp"
#include <math.h>
#include "stb_image.h"


void draw_symmetric_circ_points(int xC, int yC, int x, int y) {
    glVertex2f((float)(xC + x), (float)(yC + y));
    glVertex2f((float)(xC - x), (float)(yC + y));
    glVertex2f((float)(xC + x), (float)(yC - y));
    glVertex2f((float)(xC - x), (float)(yC - y));
    glVertex2f((float)(xC + y), (float)(yC + x));
    glVertex2f((float)(xC - y), (float)(yC + x));
    glVertex2f((float)(xC + y), (float)(yC - x));
    glVertex2f((float)(xC - y), (float)(yC - x));
}

void gl_draw_circle(int xC, int yC, int r, int t) {
    glColor3f(1, 1, 1);
    int num_segments = 100;
    for (int i = 0; i < t; i++) {  // Draw multiple rings for thickness
        float radius = r + i;
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < num_segments; j++) {
            float theta = 2.0f * M_PI * j / num_segments;
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            glVertex2f(xC + x, yC + y);
        }
        glEnd();
    }
}

void gl_draw_filled_circle(int xC, int yC, int r) {
    int num_segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xC, yC);

    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * i / num_segments;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(xC + x, yC + y);
    }
    
    glEnd();
}

void render_text(std::string text, float x, float y) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

GLFWwindow* init_opengl(int resolution_x, int resolution_y) {
    GLFWwindow* window;

    if(!glfwInit()) {
        return nullptr;
    }

    window = glfwCreateWindow(resolution_x, resolution_y, "osu! clone", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, resolution_x, resolution_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, resolution_x, 0, resolution_y, -1, 1);
    
    return window;
}

void drawCube() {
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);  // Move cube back

    static float angle = 0.0f;
    angle += 0.5f; // Rotate slightly every frame

    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);

    // Front Face
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // Back Face
    glColor3f(0.0f, 1.0f, 0.0f);  // Green
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);

    // Top Face
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);

    // Bottom Face
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // Right Face
    glColor3f(1.0f, 0.0f, 1.0f);  // Magenta
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);

    // Left Face
    glColor3f(0.0f, 1.0f, 1.0f);  // Cyan
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    glEnd();
}

void enable3D(int resolution_x, int resolution_y) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)resolution_x / (double)resolution_y, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}


void enable2D(int resolution_x, int resolution_y) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, resolution_x, 0, resolution_y, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}
