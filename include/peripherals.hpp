#ifndef PERIPHERALS_HPP
#define PERIPHERALS_HPP

#include "main.h"


class Peripherals {
    private:
        pros::Motor mainTop;
        pros::Motor mainBot;
        pros::Motor indexer;
        pros::Motor intake;
    public:
        Peripherals();
        void moveFly(int power);
        void moveInd(int power);
        void moveInt(int power);
        void pidMoveFly(double position, std::int32_t velocity);
        void pidMoveInd(double position, std::int32_t velocity);
        void pidMoveInt(double position, std::int32_t velocity);
        void printFlyVel(int line);
        void printFlyTemp(int line);
        double getTopVel();
};

#endif