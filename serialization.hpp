#ifndef SERIALIZATION_H 
#define SERIALIZATION_H 

#include <vector>
#include <iostream>
#include <vector>
#include "game.hpp"

void serialize_circles(const std::vector<Circle>& circles, const std::string& filename);

std::vector<Circle> deserialize_circles(const std::string& filename);

/* makes a playable version of a osu beatmap file */
std::vector<Circle> deserialize_osu(const std::string& filename, const int screen_width, const int screen_height);

#endif
