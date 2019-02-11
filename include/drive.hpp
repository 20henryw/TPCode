#ifndef drive_hpp
#define drive_hpp

#include "main.h"

class Drive {
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
        void pidMoveLeft(double position, std::int32_t velocity);
        void pidMoveRight(double position, std::int32_t velocity);
        void pidMove(double position, std::int32_t velocity);
        void pidTurn(double position, std::int32_t velocity);


};

#endif