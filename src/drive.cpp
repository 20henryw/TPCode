#include "main.h"
#include "drive.hpp"

Drivetrain::Drivetrain(pros::Motor left, pros::Motor right) : lDrive(left), rDrive(right) 
{
}

void Drivetrain::move(pros::Controller master){
    lDrive.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    rDrive.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    pros::delay(20);

}