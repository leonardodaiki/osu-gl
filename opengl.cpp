#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>

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

void gl_draw_circle(int xC, int yC, int r) {
    int x = 0;
    int y = r;

    int p = 1 - r;

    glBegin(GL_POINTS);
    draw_symmetric_circ_points(xC, yC, x, y);
    while (x < y) {
        x++;
        if (p > 0) {
            y--;
            p += 2 * x - 2 * y + 1;
        } else {
            p += 2 * x + 1;
        }
        draw_symmetric_circ_points(xC, yC, x, y);
    }
    glEnd();
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
