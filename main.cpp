#include <GL/gl.h>
#include <iostream>
#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <math.h>
#include "opengl.hpp"
#include "input.hpp"
#include "game.hpp"
#include "serialization.hpp"

int main(void) {
    const int screen_width = 1200;
    const int screen_height = 900;

    GLFWwindow* window = init_opengl(1200, 900);

    std::vector<Circle> map_circles = deserialize_osu("anoyo.osu", screen_width, screen_height);
    Beatmap map(map_circles);

    Game game(window, map);
    Input input(GLFW_KEY_Z, GLFW_KEY_X, window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
