#ifndef DRIVE_HPP
#define DRIVE_HPP

#include "main.h"

class Drive
{
  private:
    pros::Motor lFDrive;
    pros::Motor lBDrive;
    pros::Motor rFDrive;
    pros::Motor rBDrive;

  public:
    Drive();
    void moveLeft(int power);
    void moveRight(int power);
    void moveAll(int power);
    void setSpeed(int speed);
    void reset(); 
    bool isDriving(); 
    void PIDDrive(int driveTarget);
    void slowPIDDrive(int driveTarget);
    void turnTask(void* parameter);
    void rightSlew(int rightTarget);
    void leftSlew(int leftTarget);
    void pidMoveLeft(double position, std::int32_t velocity);
    void pidMoveRight(double position, std::int32_t velocity);
    void pidMoveAll(double position, std::int32_t velocity);
    void pidTurn(double position, std::int32_t velocity);
    void tareMotors();
    void actualDrive(int sp);
    void actualTurn(int sp);
    bool isStopped();
    void waitForDriveCompletion();
    void waitForLeftCompletion();
    void waitForRightCompletion();
    void waitForStop();
};

#endif