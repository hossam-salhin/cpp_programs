#include "simulator.h"
#include <iostream>
#include <cctype>

void Simulator::run()
{
    std::string direction;
    double distance;

    logger.log(logLevel::START, {{0.0, 0.0}, "start", 0.0});

    while(true)
    {
        std::cout << "Enter the direction (n/s/e/w or q): ";
        std::cin >> direction;
        for(char& c:direction)
        {
            c = std::tolower(c);
        }

        if (direction == "q")
        {
            logger.log(logLevel::END, {robot.getPosition(), "quit", 0.0});
            break;
        }

        std::cout << "Distance: ";
        std::cin >> distance;

        robot.move(direction, distance);

        Movement m = {robot.getPosition(), direction, distance};
        logger.log(logLevel::INFO , m);

        std::cout << "Position: (" << robot.getPosition().x << ", " << robot.getPosition().y << ")\n";

    }
}