#include <GLFW/glfw3.h>
#include "input.hpp"
#include <iostream>

void Input::update_get_status() {
    bool key_one_cur_pressed = glfwGetKey(window, keycode_one) == GLFW_PRESS;
    bool key_two_cur_pressed = glfwGetKey(window, keycode_two) == GLFW_PRESS;
    
    key_one = key_one_cur_pressed && ! was_key_one;
    key_two = key_two_cur_pressed && ! was_key_two;

    was_key_one = key_one_cur_pressed;
    was_key_two = key_two_cur_pressed;
}
