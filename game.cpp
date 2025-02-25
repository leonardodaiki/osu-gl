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

    if(!active_circles.empty()) {
        if(clock >= active_circles.front().timestamp + 100) {
            active_circles.erase(active_circles.begin());
        }
    }

    return 0;
}

int Game::render_circles() {
    if(active_circles.empty()) return 0;

for (auto it = active_circles.rbegin(); it != active_circles.rend(); ++it) {
    Circle& c = *it;
    if (clock >= c.timestamp - 700 && clock <= c.timestamp + 100) {
        draw_circle(c);
    }
}

    return 0;
}

int Game::draw_circle(Circle c) {
    glColor3f(1, 1, 1);
    gl_draw_filled_circle(c.x, c.y, map.circle_size * 20); 
    glColor3f(0.7, 0.30, 0.40);
    gl_draw_filled_circle(c.x, c.y, map.circle_size * 20 * 0.92); 
    glColor3f(1, 1, 1);

    int approach_circle_radius = 0;
    if(c.timestamp - clock >= 0) {
        approach_circle_radius = c.timestamp - clock;
    }
    gl_draw_circle(c.x, c.y, map.circle_size * 20 + approach_circle_radius * 0.18, 4); 

    return 0;
}

int Game::key_press() {
    if(active_circles.empty()) {
        return 0;
    }

    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);

    Circle c = active_circles.front();
    
    y = std::abs(900 - y);

    double dist_x = x - c.x;
    double dist_y = y - c.y;

    if(clock >= c.timestamp - 700 && clock <= c.timestamp + 100) {
        if(sqrt((dist_x * dist_x) + (dist_y * dist_y)) <= map.circle_size * 20) {
            audio.play_hitsound();
            score += 100;
            if(!active_circles.empty()) {
                active_circles.erase(active_circles.begin());
            }   
        }
    }

    return 0;
}
