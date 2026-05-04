#include "logger.h"
#include <fstream>
#include <ctime>

void Logger::log(logLevel level, const Movement &movement)
{
    std::ofstream logFile(this->logPath, std::ios_base::app);
    if(!logFile.is_open()) { return;}
    time_t now = time(0);
    std::string timeStr = ctime(&now);
    timeStr.pop_back();

    std::string levelStr;
    switch(level) {
        case logLevel::INFO: levelStr = "INFO"; break;
        case logLevel::ERROR: levelStr = "ERROR"; break;
        case logLevel::START: levelStr = "START"; break;
        case logLevel::END: levelStr = "END"; break;
    }

    logFile << "[" << timeStr << "] " 
            << levelStr << ": Moved " << movement.distance 
            << " units towards " << movement.direction 
            << " to position (" << movement.position.x << ", " << movement.position.y << ")\n";

}