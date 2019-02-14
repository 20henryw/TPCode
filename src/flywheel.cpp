#include "main.h"
#include "flywheel.hpp"

const int FLY_MAIN_PORT = 0;
const int FLY_IND_PORT = 0;

const pros::motor_gearset_e_t FLY_MAIN_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t FLY_IND_GEAR = pros::E_MOTOR_GEARSET_18;

const bool FLY_MAIN_REVERSE = false;
const bool FLY_IND_REVERSE = false;

Flywheel::Flywheel() :
    flyMain(FLY_MAIN_PORT, FLY_MAIN_GEAR, FLY_MAIN_REVERSE),
    flyInd(FLY_IND_PORT, FLY_IND_GEAR, FLY_IND_REVERSE)
    {}

/**
 * Positive power speeds up main flywheel motor
 */
void Flywheel::moveMain(int power) {
    flyMain.move(power);
}

/**
 * Moves the indexer up by applying negative power to the indexer motor
 */
void Flywheel::moveIndUp(int power) {
    flyInd.move(-power);
}

/**
 * Moves the indexer down, adding power to the flywheel by applying pos power
 * to the indexer motor
 */
void Flywheel::moveIndDown(int power) {
    flyInd.move(power);
}
