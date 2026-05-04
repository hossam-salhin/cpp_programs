#pragma once 
#include "movement.h"

class Robot {
    Position position;
    double totalDistance;

    public:
    Robot();

    void move(const std::string &direction, double distance);

    Position getPosition() const;

    double getTotalDistance() const;

    double getDisplacement() const;
    
};