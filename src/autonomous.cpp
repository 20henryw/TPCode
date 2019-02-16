#include "main.h"
using namespace okapi;

Drive* drA = new Drive();
Peripherals* peA = new Peripherals();

const int PID_VEL = 120;
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

/*
pros::Motor leftFront(11, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(3, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(2, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(4, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel1(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(6, pros::E_MOTOR_ENCODER_DEGREES);
*/


void redFront() {

    //pid drive doesn't go straight for some reason, need to multiply right side by a constant
    //drive forward and pick up ball
    peA->moveFly(94);
    peA->moveInt(30);
    peA->moveInd(-50);
    drA->pidMoveAll(3.4, PID_VEL);
    pros::Task::delay(2400);
    
    drA->moveAll(-100);
    peA->pidMoveInt(2, 127);
    peA->moveInd(-50);
    pros::Task::delay(100);
    peA->moveInd(0);

    //back up into wall
    pros::Task::delay(1200);
    drA->moveAll(-20);
    pros::Task::delay(300);

    drA->pidMoveAll(.4, 80);
    pros::Task::delay(500);
    drA->pidTurn(-.78, PID_VEL);
    pros::Task::delay(1000);
    peA->pidMoveInd(.25, 200);
    pros::Task::delay(400);


}

/**
 * 
 * to use functions from the Drive dr, use the following notation. ask rithvik if it doens't work
 * drA->functionName();
 **/
void autonomous() {
    redFront();
}

/**
 * Red back. Shoots High middle, then turns and gets ball under cap, then parks.
 ***/
/*
void auton0() {
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel1(1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel2(12, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intake(6, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    ChassisControllerIntegrated drive_controller = ChassisControllerFactory::create(
    leftF, rightF, rightB, leftB,
	AbstractMotor::gearset::green,
	{4_in, 15.5_in}
    );

    flywheel1.move(94);
    flywheel2.move(94);

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
    pros::Task::delay(1250);
    leftF.move(-5);
    leftB.move(-5);
    rightF.move(-5);
    rightB.move(-5);
}
*/
/**
 * Blue back. Shoots High middle, then turns and gets ball under cap, then parks.
 ***/
/*
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

    flywheel1.move(94);
    flywheel2.move(94);

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
    pros::Task::delay(1250);
    leftF.move(-5);
    leftB.move(-5);
    rightF.move(-5);
    rightB.move(-5);
}
*/

/**
 * Red front. Shoots all 3 flags
 ***/
/*
void auton2() {
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

    
    //intake first ball and back up, lower ball from flywheel
    intake.move(127);
    drive_controller.moveDistanceAsync(45_in);
    drive_controller.waitUntilSettled();
    intake.move(-127);
    pros::Task::delay(100);
    intake.move(0);

    //turn flywheel on
    flywheel1.move(94);
    flywheel2.move(94);

    //back up, align with wall
    leftF.move(-80);
    leftB.move(-80);
    rightF.move(-80);
    rightB.move(-80);
    pros::Task::delay(2000);
    leftF.move(0);
    leftB.move(0);
    rightF.move(0);
    rightB.move(0);

    //move forward, turn left, back up
    drive_controller.moveDistanceAsync(6.5_in);
    drive_controller.waitUntilSettled();
    drive_controller.turnAngleAsync(-75_deg);
    drive_controller.waitUntilSettled();
    pros::Task::delay(150);
    drive_controller.moveDistanceAsync(-8_in);
    drive_controller.waitUntilSettled();
    
    //shoot high flag, shoot middle, drive into low
    intake.move(127);
    pros::Task::delay(300);
    intake.move(0);
    drive_controller.moveDistanceAsync(35_in);
    drive_controller.waitUntilSettled();
    intake.move(127);
    pros::Task::delay(1000);
    intake.move(0);
    flywheel1.move(0);
    flywheel2.move(0);
    leftF.move(60);
    leftB.move(60);
    rightF.move(90);
    rightB.move(90);
    pros::Task::delay(750);
    leftF.move(0);
    leftB.move(0);
    rightF.move(0);
    rightB.move(0);

    //back up, turn left, flip cap
    drive_controller.moveDistanceAsync(-20_in);
    drive_controller.waitUntilSettled();
    drive_controller.turnAngleAsync(90_deg);

}
*/

/**
 * Blue front. Shoots all 3 flags
 ***/
/*
void auton3() {
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

    
    //intake first ball and back up, lower ball from flywheel
    intake.move(127);
    drive_controller.moveDistanceAsync(45_in);
    drive_controller.waitUntilSettled();
    intake.move(-127);
    pros::Task::delay(100);
    intake.move(0);

    //turn flywheel on
    flywheel1.move(94);
    flywheel2.move(94);

    //back up, align with wall
    leftF.move(-80);
    leftB.move(-80);
    rightF.move(-80);
    rightB.move(-80);
    pros::Task::delay(2000);
    leftF.move(0);
    leftB.move(0);
    rightF.move(0);
    rightB.move(0);

    //move forward, turn left, back up
    drive_controller.moveDistanceAsync(6.5_in);
    drive_controller.waitUntilSettled();
    drive_controller.turnAngleAsync(75_deg);
    drive_controller.waitUntilSettled();
    pros::Task::delay(150);
    drive_controller.moveDistanceAsync(-8_in);
    drive_controller.waitUntilSettled();
    
    //shoot high flag, shoot middle, drive into low
    intake.move(127);
    pros::Task::delay(300);
    intake.move(0);
    drive_controller.moveDistanceAsync(35_in);
    drive_controller.waitUntilSettled();
    intake.move(127);
    pros::Task::delay(1000);
    intake.move(0);
    flywheel1.move(0);
    flywheel2.move(0);
    leftF.move(90);
    leftB.move(90);
    rightF.move(60);
    rightB.move(60);
    pros::Task::delay(750);
    leftF.move(0);
    leftB.move(0);
    rightF.move(0);
    rightB.move(0);

    //back up, turn left, flip cap
    drive_controller.moveDistanceAsync(-20_in);
    drive_controller.waitUntilSettled();
    drive_controller.turnAngleAsync(90_deg);

}
*/

/*
void autonomous() {
    switch (0) {
        //red back
        case 0: auton0();
        break;
        //blue back
        case 1: auton1();
        break;
        //red front
        case 2: auton2();
        break;
        //blue front
        case 3: auton3();
        break;
    }
}
*/
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