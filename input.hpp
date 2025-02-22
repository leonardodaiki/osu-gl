#ifndef INPUT_H
#define INPUT_H

#include "GLFW/glfw3.h"

struct Input {
    const int keycode_one;
    const int keycode_two;

    GLFWwindow* window;

    bool key_one;
    bool key_two;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    Input(int KEY_ONE_, int KEY_TWO_, GLFWwindow* window_) : keycode_one(KEY_ONE_), keycode_two(KEY_TWO_), window(window_) {}

    void update_get_status();

    private:
        bool was_key_one;
        bool was_key_two;
};

#endif
