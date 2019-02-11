#include "main.h"
#include "drive.hpp"

// what are these lol
#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

const int LF_PORT = 8;
const int LB_PORT = 19;
const int RF_PORT = 10;
const int RB_PORT = 20;

const pros::motor_gearset_e_t LF_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t LB_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t RF_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t RB_GEAR = pros::E_MOTOR_GEARSET_18;

const bool LF_REVERSE = false;
const bool LB_REVERSE = false;
const bool RF_REVERSE = true;
const bool RB_REVERSE = true;



Drive::Drive() : 
    lFDrive(LF_PORT, LF_GEAR, LF_REVERSE), 
    lBDrive(LB_PORT, LB_GEAR, LB_REVERSE), 
    rFDrive(RF_PORT, RF_GEAR, RF_REVERSE), 
    rBDrive(RB_PORT, RB_GEAR, RB_REVERSE) {
      pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD);
      lFDrive.set_pos_pid(pid);
      lBDrive.set_pos_pid(pid);
      rFDrive.set_pos_pid(pid);
      rBDrive.set_pos_pid(pid);
}

void Drive::moveLeft(int power) {
    lFDrive.move(power);
    lBDrive.move(power);
}

void Drive::moveRight(int power) {
    rFDrive.move(power);
    rBDrive.move(power);
}

void Drive::moveAll(int power) {
    moveLeft(power);
    moveRight(power);
}

void Drive::pidMoveLeft(double position, std::int32_t velocity) {
    lFDrive.move_relative(position, velocity);
    lBDrive.move_relative(position, velocity);
}

void Drive::pidMoveRight(double position, std::int32_t velocity) {
    rFDrive.move_relative(position, velocity);
    rBDrive.move_relative(position, velocity);
    
}

void Drive::pidMove(double position, std::int32_t velocity) {
    pidMoveLeft(position, velocity);
    pidMoveRight(position, velocity);
}

