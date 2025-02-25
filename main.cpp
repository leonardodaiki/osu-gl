#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <chrono>
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
#include "menu.hpp"

int main(int argc, char** argv) {
    std::string song_name = "lost";

    std::string music_file_name = "./maps/" + song_name + ".wav";
    std::string circles_file_name = "./maps/" + song_name + ".osu";

    glutInit(&argc, argv);

    const int screen_width = 1200;
    const int screen_height = 900;

    GLFWwindow* window = init_opengl(1200, 900);

    std::vector<Circle> map_circles = deserialize_osu(circles_file_name, screen_width, screen_height);
    Beatmap map(map_circles);
    serialize_circles(map_circles, "bluenation_debug");
    Game game(window, map, music_file_name);
    Input input(GLFW_KEY_Z, GLFW_KEY_X, window);

    int on_menu = 1;
    int sound_playing = 0;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(on_menu) {
            on_menu = draw_menu(screen_width, screen_height, window);
        } else {
            if(sound_playing == 0) {
                game.clock = 0;
                game.start_time = std::chrono::steady_clock::now();
                game.audio.play_music();
                sound_playing = 1;
            }
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
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
