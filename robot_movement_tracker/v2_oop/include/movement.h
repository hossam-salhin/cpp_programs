#pragma once 
#include <string>

struct Position {
    double x;
    double y;
};

struct Movement {
    Position position;
    std::string direction;
    double distance;
};