#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
#include <iostream>
#include <string>
#define GL_SILENCE_DEPRECATION
#define MINIAUDIO_IMPLEMENTATION

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "opengl.hpp"
#include "input.hpp"
#include "game.hpp"
#include "serialization.hpp"
#include "audio.hpp"

int main(int argc, char** argv) {
    std::string music_file_name = "infinite.wav";
    std::string circles_file_name = "infinite.osu";

    glutInit(&argc, argv);

    const int screen_width = 1200;
    const int screen_height = 900;

    GLFWwindow* window = init_opengl(1200, 900);

    std::vector<Circle> map_circles = deserialize_osu(circles_file_name, screen_width, screen_height);
    Beatmap map(map_circles);

    Game game(window, map, music_file_name);
    Input input(GLFW_KEY_Z, GLFW_KEY_X, window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        enable3D(screen_width, screen_height);

        drawCube();

        enable2D(screen_width, screen_height);

        game.get_current_time();
        game.get_active_circles();
        game.render_circles();
        input.update_get_status();
        if(input.key_one) {
            game.key_press();
        }
        if(input.key_two) {
            game.key_press();
        }

        render_text(std::to_string(game.score), 0, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
