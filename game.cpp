#include "game.hpp"
#include "opengl.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>

int Game::get_current_time() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - start_time;
    clock = elapsed.count() * 1000;
    return 0;
}

int Game::get_active_circles() {
    
    // this should increase performance because we are not O(N) going through the entire vec
    // but it also assumes that the vector is sorted by timestamps
    Circle c = map.circle_vec.front();
    if(clock >= c.timestamp - 5000){
        active_circles.push_back(c);
        if(!map.circle_vec.empty()) {
            map.circle_vec.erase(map.circle_vec.begin());
        }
    }

    if(clock >= active_circles.front().timestamp + 100) {
        active_circles.erase(active_circles.begin());
    }

    return 0;
}

int Game::render_circles() {
    if(active_circles.empty()) return 0;

    for(Circle c : active_circles) {
        if(clock >= c.timestamp - 700 && clock <= c.timestamp + 100){
            draw_circle(c); 
        }
    }

    return 0;
}

int Game::draw_circle(Circle c) {
    gl_draw_circle(c.x, c.y, map.circle_size * 20); 

    int approach_circle_radius = 0;
    if(c.timestamp - clock >= 0) {
        approach_circle_radius = c.timestamp - clock;
    }
    gl_draw_circle(c.x, c.y, map.circle_size * 20 + approach_circle_radius * 0.18); 

    return 0;
}

int Game::key_press() {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);

    Circle c = active_circles.front();
    
    y = std::abs(900 - y);

    double dist_x = x - c.x;
    double dist_y = y - c.y;


    std::cout << "cursor pos: " << x << " " << y << std::endl;
    std::cout << "next circle pos: " << c.x << " " << c.y << std::endl;
    std::cout << "distance: " << dist_x << " " << dist_y << std::endl;
    std::cout << sqrt((dist_x * dist_x) + (dist_y * dist_y)) << std::endl;
    std::cout << map.circle_size * 20 << std::endl;
    
    if(clock >= c.timestamp - 700 && clock <= c.timestamp + 100) {
        if(sqrt((dist_x * dist_x) + (dist_y * dist_y)) <= map.circle_size * 20) {
            std::cout << " ERASED " << std::endl;
            if(!active_circles.empty()) {
                active_circles.erase(active_circles.begin());
            }   
        }
    }

    return 0;
}
