#include "robot.h"
#include <cmath>


Robot::Robot(): position{0.0 , 0.0}, totalDistance(0.0) {}


void Robot::move(const std::string &direction, double distance)
{
    if(direction == "n") { position.y += distance;}
    else if (direction == "s") { position.y -= distance;}
    else if (direction == "e") { position.x += distance;}
    else if (direction == "w") { position.x -= distance;}
}

Position Robot::getPosition() const
{
    return position;
}

double Robot::getTotalDistance() const
{
    return totalDistance;
}

double Robot::getDisplacement() const
{
    return std::sqrt(pow(position.x, 2) + pow(position.y, 2));
}