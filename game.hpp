#ifndef GAME_H 
#define GAME_H 

#include <vector>
#include <chrono>
#include <GLFW/glfw3.h>

struct Circle {
    int x;
    int y;
    int timestamp;
    bool new_combo;

    Circle(int x_, int y_, int timestamp_, bool new_combo_) : x(x_), y(y_), timestamp(timestamp_), new_combo(new_combo_) {}
    Circle() : x(0), y(0), timestamp(0), new_combo(0) {}
};

struct Beatmap {
    int circle_size;
    //float approach_rate;
    //float overall_difficulty;

    std::vector<Circle> circle_vec;

    Beatmap(std::vector<Circle> vec) : circle_vec(vec), circle_size(4) {}
};

struct Game {
    std::chrono::steady_clock::time_point start_time;
    //GLFWwindow* window;
    std::vector<Circle> active_circles;
    Beatmap map;
    int clock;
    
    Game(Beatmap map_) : start_time(std::chrono::steady_clock::now()), map(map_), clock(0) {}
    int get_current_time();
    int get_active_circles();
    int render_circles();
    int draw_circle(Circle c);
};

#endif
