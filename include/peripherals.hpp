#ifndef PERIPHERALS_HPP
#define PERIPHERALS_HPP

#include "main.h"

class Peripherals
{
  private:
    pros::Motor mainTop;
    pros::Motor indexer;
    pros::Motor intake;
    pros::Motor scraper;

  public:
    Peripherals();
    void moveFly(int power);
    void moveInd(int power);
    void moveInt(int power);
    void moveScr(int power);
    void pidMoveFly(double position, std::int32_t velocity);
    void pidMoveInd(double position, std::int32_t velocity);
    void pidMoveInt(double position, std::int32_t velocity);
    void pidMoveScr(double position, std::int32_t velocity);
    void scrBrake(pros::motor_brake_mode_e_t mode); 
    void resetScr();
    void pidAbsScr(double position, std::int32_t velocity);
    void printFlyVel(int line);
    void printPressed(int line);
    void printFlyTemp(int line);
    void printFlyPow(int line);
    double getTopVel();
    double getScrPos();
    void scrBase();
    void tareScr();
};

#endif