#include "main.h"
using namespace okapi;

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

/**
 * Red back. Shoots High middle, then turns and gets ball under cap, then parks.
 ***/
void auton0() {
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel1(1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel2(12, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intake(6, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    ChassisControllerIntegrated drive_controller = ChassisControllerFactory::create(
    leftF, rightF, rightB, leftB,
	AbstractMotor::gearset::green,
	{4_in, 15.5_in}
    );

    flywheel1.move(127);
    flywheel2.move(127);

    pros::Task::delay(5000);

    intake.move(127);
    pros::Task::delay(1500);
    flywheel1.move(0);
    flywheel2.move(0);
    drive_controller.turnAngleAsync(55_deg);
    drive_controller.waitUntilSettled();
    pros::Task::delay(50);
    drive_controller.moveDistanceAsync(43_in);
    drive_controller.waitUntilSettled();
    intake.move(0);
    drive_controller.moveDistance(-5_in);
    drive_controller.waitUntilSettled();   
    drive_controller.turnAngle(-88_deg);
    pros::Task::delay(50);
    drive_controller.waitUntilSettled();
    leftF.move(127);
    leftB.move(127);
    rightF.move(117);
    rightB.move(117);
    pros::Task::delay(975);
    leftF.move(-.1);
    leftB.move(-.1);
    rightF.move(-.1);
    rightB.move(-.1);
}

/**
 * Blue back. Shoots High middle, then turns and gets ball under cap, then parks.
 ***/
void auton1() {
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel1(1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel2(12, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intake(6, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    ChassisControllerIntegrated drive_controller = ChassisControllerFactory::create(
    leftF, rightF, rightB, leftB,
	AbstractMotor::gearset::green,
	{4_in, 15.5_in}
    );

    flywheel1.move(127);
    flywheel2.move(127);

    pros::Task::delay(5000);

    intake.move(127);
    pros::Task::delay(1500);
    flywheel1.move(0);
    flywheel2.move(0);
    drive_controller.turnAngleAsync(-55_deg);
    drive_controller.waitUntilSettled();
    pros::Task::delay(50);
    drive_controller.moveDistanceAsync(43_in);
    drive_controller.waitUntilSettled();
    intake.move(0);
    drive_controller.moveDistance(-5_in);
    drive_controller.waitUntilSettled();   
    drive_controller.turnAngle(88_deg);
    pros::Task::delay(50);
    drive_controller.waitUntilSettled();
    leftF.move(117);
    leftB.move(117);
    rightF.move(127);
    rightB.move(127);
    pros::Task::delay(975);
    leftF.move(-5);
    leftB.move(-5);
    rightF.move(-5);
    rightB.move(-5);
}

void autonomous() {
    switch (1) {
        case 0: auton0();
        break;
        case 1: auton1();
        break;
    }
}

/**
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
*/