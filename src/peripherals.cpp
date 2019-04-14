#include "main.h"
#include "peripherals.hpp"

// what are these lol
#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

const int MAIN_TOP_PORT = 1;
const int INDEXER_PORT = 3;
const int INTAKE_PORT = 2;
const int SCRAPER_PORT = 4;

const pros::motor_gearset_e_t SCRAPER_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t MAIN_TOP_GEAR = pros::E_MOTOR_GEARSET_06;
const pros::motor_gearset_e_t INTAKE_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t INDEXER_GEAR = pros::E_MOTOR_GEARSET_06;

const bool MAIN_TOP_REVERSE = false;
const bool INDEXER_REVERSE = true;
const bool INTAKE_REVERSE = true;
const bool SCRAPER_REVERSE = true;

Peripherals::Peripherals() : mainTop(MAIN_TOP_PORT, MAIN_TOP_GEAR, MAIN_TOP_REVERSE),
                             indexer(INDEXER_PORT, INDEXER_GEAR, INDEXER_REVERSE),
                             intake(INTAKE_PORT, INTAKE_GEAR, INTAKE_REVERSE),
                             scraper(SCRAPER_PORT, SCRAPER_GEAR, SCRAPER_REVERSE)
{
    pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD);
    mainTop.set_pos_pid(pid);
    indexer.set_pos_pid(pid);
    intake.set_pos_pid(pid);
    scraper.set_pos_pid(pid);

    mainTop.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    indexer.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    intake.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    scraper.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
}

void Peripherals::moveFly(int power)
{
    mainTop.move(power);
}

void Peripherals::moveInd(int power)
{
    indexer.move(power);
}

void Peripherals::moveInt(int power)
{
    intake.move(power);
}

void Peripherals::moveScr(int power)
{
    scraper.move(power);
}

void Peripherals::scrBrake(pros::motor_brake_mode_e_t mode) 
{
    scraper.set_brake_mode(mode); 
}

void Peripherals::resetScr()
{
      pidAbsScr(0, 100);
      pros::Task::delay(400);
}

void Peripherals::pidAbsScr(double position, std::int32_t velocity)
{
    scraper.move_absolute(position, velocity);
}

void Peripherals::pidMoveFly(double position, std::int32_t velocity)
{
    mainTop.move_relative(position, velocity);
}

void Peripherals::pidMoveInd(double position, std::int32_t velocity)
{
    indexer.move_relative(position, velocity);
}

void Peripherals::pidMoveInt(double position, std::int32_t velocity)
{
    intake.move_relative(position, velocity);
}

void Peripherals::pidMoveScr(double position, std::int32_t velocity)
{
    scraper.move_relative(position, velocity);
}

void Peripherals::printFlyVel(int line)
{
    pros::lcd::set_text(line, "Flywheel RPM: " + std::to_string(mainTop.get_actual_velocity()));
}

void Peripherals::printFlyTemp(int line)
{
    pros::lcd::set_text(line, "Flywheel Temp: " + std::to_string(mainTop.get_temperature()));
}

void Peripherals::printFlyPow(int line) 
{
    pros::lcd::set_text(line, "Flywheel Pow: " + std::to_string(mainTop.get_power()));
}

void Peripherals::printPressed(int line)
{
    pros::lcd::set_text(line, "B pressed: ");
}

double Peripherals::getTopVel()
{
    return mainTop.get_actual_velocity();
}

double Peripherals::getScrPos()
{
    return scraper.get_position();
}

/*
* Moves the scarper to the base firing position and tares the motor encoder at that position
*/
void Peripherals::scrBase()
{
    moveScr(127);
    pros::Task::delay(300);
    pidMoveScr(-.05, 150);
    pros::Task::delay(400);
    scraper.tare_position();
}