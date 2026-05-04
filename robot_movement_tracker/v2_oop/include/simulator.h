#pragma once
#include "robot.h"
#include "logger.h"


class Simulator {
    Robot robot;
    Logger logger;

    public:
    void run();
};