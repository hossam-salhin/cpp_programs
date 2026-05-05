#include "simulator.h"
#include <iostream>
#include <cctype>
#include <limits>

void Simulator::run()
{
    std::string direction;
    double distance;

    logger.log(logLevel::START, {{0.0, 0.0}, "start", 0.0});

    while(true)
    {
        std::cout << "Enter the direction (n/s/e/w or q): ";
        while(true)
        {
            std::cin >> direction;
            for(char& c:direction)
            {
                c = std::tolower(c);
            }
            if (std::cin && (direction == "n" || direction == "s" || direction == "e" || direction == "w" || direction == "q" ))
            {
                break;
            }
            else {
                std::cout << "Invalid input, Please enter (n/s/e/w or q): ";
                logger.log(logLevel::ERROR, {robot.getPosition(), "Invalid direction", 0.0});
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            }
        }

        

        if (direction == "q")
        {
            logger.log(logLevel::END, {robot.getPosition(), "quit", 0.0});
            std::cout << "Robot final position is: (" << robot.getPosition().x << " , " << robot.getPosition().y << ")\n"
                        << "Total distance moved: "<< robot.getTotalDistance() 
                        << "\nTotal displacement is: "<< robot.getDisplacement() << std::endl;
            break;
        }

        std::cout << "Distance: ";
        while (true) {
            std::cin >> distance;
            if (std::cin.fail() || distance <= 0) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid distance. Please enter a positive number greater than zero: ";
            }
            else {
                break; // valid input, exit the loop
            }
        }   

        robot.move(direction, distance);

        Movement m = {robot.getPosition(), direction, distance};
        logger.log(logLevel::INFO , m);

        std::cout << "Position: (" << robot.getPosition().x << ", " << robot.getPosition().y << ")\n";

    }
}