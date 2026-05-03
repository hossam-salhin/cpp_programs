#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <limits>
#include <cctype>


enum logLevel{
    INFO,
    ERROR,
    START,
    END
};
struct Position {
    double x;
    double y;
};
struct Movement { 
    Position position;
    std::string direction;
    double distance;
};

void logMovement(logLevel level, const Movement& movement)
{
    std::ofstream file("movement_log.txt", std::ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        std::string timestr = ctime(&now);
        timestr.pop_back(); // remove the newline character from the end of the timestamp
        std::string levelstr;
        if(level == INFO) {levelstr = "[INFO]";}
        else if (level == ERROR) {levelstr = "[ERROR]";}
        else if (level == START) {levelstr = "[START]";}
        else if (level == END) {levelstr = "[END]";}
        file << "Time: " << "[" << timestr << "] " << levelstr << " Position: (" << movement.position.x << ", " << movement.position.y 
                << ") " << "Direction: " << movement.direction << " " << "Distance: " << movement.distance << std::endl;
        file << "-----------------------------" << std::endl;
        file.close();

    }
    else {
        std::cout << "Unable to open the file." << std::endl;
    }
}

bool updatePosition(Position& currentPosition, const std::string& direction, double distance)
{
    Position newPosition = currentPosition;
    if (direction == "n") {
        currentPosition.y += distance;
    }
    else if (direction == "s") {
        currentPosition.y -= distance;
    }
    else if (direction == "e") {
        currentPosition.x += distance;
    }
    else if (direction == "w") {
        currentPosition.x -= distance;
    }
    else{return false;}

    return true; 

}

int main()
{
    Position startPostion = {0.0, 0.0};
    Position currentPosition = startPostion;
    std::string direction;
    double distance;
    double totalDistance = 0.0;
    double Displacement = 0.0;

    logMovement(START,{currentPosition, "Start", 0.0});

    while(true){
        std::cout << "Enter direction (N, S, E, W) or 'q' to quit: ";
        std::cin >> direction;
        for(char& c: direction)
        {
            c = std::tolower(c);
        }
        
        if (direction == "q") {
            logMovement(END, {currentPosition, "Quit", 0.0});
            Displacement = std::sqrt(std::pow(currentPosition.x, 2) + std::pow(currentPosition.y, 2));
            std::cout << "Exiting the program. Final Position: (" << currentPosition.x << ", " << currentPosition.y << ")" 
                << "\nTotal distance traveled: " << totalDistance << "\nDisplacement from origin: " << Displacement << std::endl;
            break;
        }
        
        std::cout << "Enter distance: ";
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
        if(!updatePosition(currentPosition, direction, distance))
        {
            std::cout << "Invalid direction. Please enter N, S, E, W or 'q' to quit." << std::endl;
            logMovement(ERROR, {currentPosition, direction, distance});
            continue;
        }
    
        
        Movement movement = {currentPosition, direction, distance};
        logMovement(INFO,movement);
        totalDistance += distance;
        std::cout << "Current Position: (" << currentPosition.x << ", " << currentPosition.y << ")" << std::endl;
    }

    return 0;
}
