#include "main.h"

pros::Motor flywheela(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakea(6, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFronta(5, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBacka(3, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightFronta(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBacka(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous2() {
    flywheela.move(-127);
    pros::Task::delay(11000);
    intakea.move(127);
    pros::Task::delay(2000);
}

void autonomous1() {
    intakea.move(127);
    leftFronta.move(80);
    leftBacka.move(80);
    rightFronta.move(-100);
    rightFronta.move(-100);
    pros::Task::delay(1400);
    leftFronta.move(-30);
    leftBacka.move(-30);
    rightFronta.move(30);
    rightFronta.move(30);
    pros::Task::delay(3000);
    leftFronta.move(0);
    leftBacka.move(0);
    rightFronta.move(0);
    rightFronta.move(0);


}

void autonomous() {
    flywheela.move(-127);
    pros::Task::delay(11000);
    intakea.move(127);
    pros::Task::delay(2000);
    leftFronta.move(97);
    leftBacka.move(97);
    rightFronta.move(-127);
    rightFronta.move(-127);
    pros::Task::delay(1500);
    leftFronta.move(0);
    leftBacka.move(0);
    rightFronta.move(0);
    rightBacka.move(0);


}