#pragma once 
#include "movement.h"
#include <string>

enum logLevel {
    INFO,
    ERROR,
    START,
    END
};

class Logger {
    std::string logPath = "../logs/movement_log.txt";
    
    public:
    void log(logLevel level, const Movement &movement);
};