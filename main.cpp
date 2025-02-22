#include <GL/gl.h>
#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <iostream>
#include "opengl.hpp"
#include "game.hpp"
#include "serialization.hpp"

int main(void) {
    const int screen_width = 1200;
    const int screen_height = 900;

    GLFWwindow* window = init_opengl(1200, 900);

    std::vector<Circle> map_circles = deserialize_osu("anoyo.osu", screen_width, screen_height);
    Beatmap map(map_circles);

    Game game(map);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        game.get_current_time();
        game.get_active_circles();
        game.render_circles();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
