#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "game.hpp"

void serialize_circles(const std::vector<Circle>& circles, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "couldn't write on file.\n";
        return;
    }

    file << "[Circles]\n";
    for (const auto& circle : circles) {
        file << circle.x << "," << circle.y << "," 
             << circle.timestamp << "," << circle.new_combo << "\n";
    }

    file.close();
}

std::vector<Circle> deserialize_circles(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Circle> circles;
    if (!file) {
        std::cerr << "couldn't read from file.\n";
        return circles;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Circle circle;
        char comma;

        ss >> circle.x >> comma >> circle.y >> comma >> circle.timestamp >> comma >> circle.new_combo;
        circles.push_back(circle);
    }

    file.close();
    return circles;
}

std::vector<Circle> deserialize_osu(const std::string& filename, const int screen_width, const int screen_height) {
    std::ifstream file(filename);
    std::vector<Circle> circles;

    if (!file) {
        std::cerr << "couldn't read from file.\n";
        return circles;
    }

    std::string line;
    
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Circle circle;
        char comma;

        const int osu_max_x = 600;
        const int osu_max_y = 400;
        const int buffer_area = 150;

        int usableWidth = screen_width - 2 * buffer_area;
        int usableHeight = screen_height - 2 * buffer_area;

        ss >> circle.x >> comma >> circle.y >> comma >> circle.timestamp;
        
        circle.x = buffer_area + (circle.x * (float)usableWidth / osu_max_x);
        circle.y = buffer_area + (circle.y * (float)usableHeight / osu_max_y);

        std::cout << circle.x << " " << circle.y << std::endl;

        circle.new_combo = 0; 

        circles.push_back(circle);
    }

    file.close();
    return circles;
}
