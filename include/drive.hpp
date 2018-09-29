#ifndef drive_hpp
#define drive_hpp

#include "main.h"

class Drivetrain {
    private:
        pros::Motor lDrive;
        pros::Motor rDrive;
    public:
        Drivetrain(pros::Motor l, pros::Motor r);
        ~Drivetrain() {}
        void move(pros::Controller master);
};

#endif