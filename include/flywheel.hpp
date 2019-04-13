#ifndef FLYWHEEL_HPP
#define FLYWHEEL_HPP

#include "main.h"

class Flywheel {
    private:
        pros::Motor flyMain;
        pros::Motor flyInd;
    public:
        Flywheel();
        void moveMain(int power);
        void moveIndUp(int power);
        void moveIndDown(int power);
};

#endif