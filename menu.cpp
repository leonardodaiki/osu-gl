#include "opengl.hpp"
#include "menu.hpp"
#include <GL/freeglut_std.h>
#include <cmath>
#include "miniaudio.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat pink[] = {0.95, 0.84, 0.85, 1.0f};


GLfloat light1_pos[] = {3.0, 5.0, 2.0, 1.0};
GLfloat light1_diffuse[] = {0.8, 0.5, 1.0, 1.0};
GLfloat light1_specular[] = {1.0, 0.8, 1.0, 1.0};

float orb_rotation = 0.0f;

float time_counter = 0.0f;

int draw_menu(int screen_width, int screen_height, GLFWwindow* window) {
    enable3D(screen_width, screen_height);

    float camera_offset = sin(time_counter) * 2.0f;

    float light0_x_offset = sin(time_counter) * 1.5f;
    float light0_y_offset = cos(time_counter) * 0.8f;
    float light1_z_offset = sin(time_counter * 1.2f) * 1.5f;

    float light0_pos[] = { light0_x_offset, 2.0f + light0_y_offset, 3.0f, 1.0f };
    float light1_pos[] = { -2.0f, 3.0f, 4.0f + light1_z_offset, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, pink);
    glLightfv(GL_LIGHT0, GL_SPECULAR, black);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glTranslatef(0, 0, -12 + camera_offset);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pink);
    glutSolidSphere(2, 100, 10);

    int num_esferas = 6;
    float raio_orbita = 4.0f;
    float tamanho_esfera = 0.5f;

    for (int i = 0; i < num_esferas; i++) {
        float angulo = (i * 2.0f * M_PI / num_esferas) + time_counter;
        float x = cos(angulo) * raio_orbita;
        float y = sin(angulo * 1.5f) * 2.0f;
        float z = sin(angulo) * raio_orbita;

        glPushMatrix();
        glTranslatef(x, y, z);
        glutSolidSphere(tamanho_esfera, 50, 10);
        glPopMatrix();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    enable2D(screen_width, screen_height);
    glColor3f(0, 0, 0);
    render_text("osu-gl!", screen_width * 0.5f, screen_height * 0.5, 0.5f + 0.2f * sin(time_counter));
    glColor3f(1, 1, 1);
    render_text("aperte enter", screen_width * 0.5f - 350, screen_height * 0.15);

    time_counter += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        return 0;    
    }
    return 1;
}
