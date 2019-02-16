#include "main.h"
#include "peripherals.hpp"

// what are these lol
#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

const int MAIN_TOP_PORT = 12;
const int MAIN_BOT_PORT = 1;
const int INDEXER_PORT = 18;
const int INTAKE_PORT = 6;

const pros::motor_gearset_e_t MAIN_TOP_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t MAIN_BOT_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t INDEXER_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t INTAKE_GEAR = pros::E_MOTOR_GEARSET_18;


const bool MAIN_TOP_REVERSE = true;
const bool MAIN_BOT_REVERSE = false;
const bool INDEXER_REVERSE = false;
const bool INTAKE_REVERSE = false;

Peripherals::Peripherals() :
    mainTop(MAIN_TOP_PORT, MAIN_TOP_GEAR, MAIN_TOP_REVERSE),
    mainBot(MAIN_BOT_GEAR, MAIN_BOT_GEAR, MAIN_BOT_REVERSE),
    indexer(INDEXER_PORT, INDEXER_GEAR, INDEXER_REVERSE),
    intake(INTAKE_PORT, INTAKE_GEAR, INTAKE_REVERSE)
    {
        pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD);
        mainTop.set_pos_pid(pid);
        mainBot.set_pos_pid(pid);
        indexer.set_pos_pid(pid);
        intake.set_pos_pid(pid);

        mainTop.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
        mainBot.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
        indexer.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
        intake.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    }

void Peripherals::moveFly(int power) {
    mainTop.move(power);
    mainBot.move(power);
}

void Peripherals::moveInd(int power) {
    indexer.move(power);
}

void Peripherals::moveInt(int power) {
    intake.move(power);
}

void Peripherals::pidMoveFly(double position, std::int32_t velocity) {
    mainTop.move_relative(position, velocity);
    mainBot.move_relative(position, velocity);
}

void Peripherals::pidMoveInd(double position, std::int32_t velocity) {
    indexer.move_relative(position, velocity);
}

void Peripherals::pidMoveInt(double position, std::int32_t velocity) {
    intake.move_relative(position, velocity);
}

void Peripherals::printFlyVel(int line) {
    pros::lcd::set_text(line, "top: " + std::to_string(mainTop.get_actual_velocity()));
    pros::lcd::set_text(line + 1, "bot: " + std::to_string(mainBot.get_actual_velocity()));
}

void Peripherals::printFlyTemp(int line) {
    pros::lcd::set_text(line, "top: " + std::to_string(mainTop.get_temperature()));
    pros::lcd::set_text(line + 1, "bot: " + std::to_string(mainBot.get_temperature()));
}

