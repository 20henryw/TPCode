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

    //move forward, turn left, shoot
    drA->pidMoveAll(.6, 80);
    pros::Task::delay(1000);
    drA->pidTurn(.77, PID_VEL);
    pros::Task::delay(1000);
    peA->pidMoveInd(1, 200);
    peA->pidMoveInt(.2, PID_VEL);
    pros::Task::delay(1000);
    
    // move forward, shoot, move forward
    drA->pidMoveAll(2.35, PID_VEL);
    pros::Task::delay(1200);
    peA->pidMoveInd(2, 200);
    peA->pidMoveInt(2, PID_VEL);
    pros::Task::delay(800);

    //hit bottom flag, back up
    drA->pidMoveAll(1.7, PID_VEL);
    pros::Task::delay(1000);
    drA->pidMoveAll(-2.2, PID_VEL);
    pros::Task::delay(1000);
    drA->pidTurn(-.78, PID_VEL);
}

void blueFront() {

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

    //move forward, turn right, shoot
    drA->pidMoveAll(.6, 80);
    pros::Task::delay(1000);
    drA->pidTurn(-.77, PID_VEL);
    pros::Task::delay(1000);
    peA->pidMoveInd(1, 200);
    peA->pidMoveInt(.2, PID_VEL);
    pros::Task::delay(1000);
    
    // move forward, shoot, move forward
    drA->pidMoveAll(2.35, PID_VEL);
    pros::Task::delay(1200);
    peA->pidMoveInd(2, 200);
    peA->pidMoveInt(2, PID_VEL);
    pros::Task::delay(800);

    //hit bottom flag, back up
    drA->pidMoveAll(1.7, PID_VEL);
    pros::Task::delay(1000);
    drA->pidMoveAll(-2.2, PID_VEL);
    pros::Task::delay(1000);
    drA->pidTurn(.78, PID_VEL);
}

/* Red back. Shoots High middle, then turns and gets ball under cap, then parks.
 ***/
void redBack() {
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel1(1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel2(12, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor indexer(18, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intake(6, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    ChassisControllerIntegrated drive_controller = ChassisControllerFactory::create(
    leftF, rightF, rightB, leftB,
	AbstractMotor::gearset::green,
	{4_in, 15.5_in}
    );

    flywheel1.move(85);
    flywheel2.move(85);

    pros::Task::delay(4700);
    intake.move(110);
    indexer.move(105);
    pros::Task::delay(1500);
    flywheel1.move(0);
    flywheel2.move(0);
    drive_controller.turnAngleAsync(48_deg);
    drive_controller.waitUntilSettled();
    pros::Task::delay(25);
    drive_controller.moveDistanceAsync(42_in);
    drive_controller.waitUntilSettled();
    intake.move(0);
    indexer.move(0);
    drive_controller.moveDistance(-6.5_in);
    drive_controller.waitUntilSettled();   
    drive_controller.turnAngle(-70_deg);
    pros::Task::delay(50);
    drive_controller.waitUntilSettled();
    leftF.move(107);
    leftB.move(107);
    rightF.move(103);
    rightB.move(103);
    pros::Task::delay(1250);
    leftF.move(-5);
    leftB.move(-5);
    rightF.move(-5);
    rightB.move(-5);
}

/* Blue back. Shoots High middle, then turns and gets ball under cap, then parks.
 ***/
void blueBack() {
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel1(1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor flywheel2(12, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor indexer(18, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intake(6, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    ChassisControllerIntegrated drive_controller = ChassisControllerFactory::create(
    leftF, rightF, rightB, leftB,
	AbstractMotor::gearset::green,
	{4_in, 15.5_in}
    );

    flywheel1.move(85);
    flywheel2.move(85);

    pros::Task::delay(4700);
    intake.move(110);
    indexer.move(105);
    pros::Task::delay(1500);
    flywheel1.move(0);
    flywheel2.move(0);
    drive_controller.turnAngleAsync(-48_deg);
    drive_controller.waitUntilSettled();
    pros::Task::delay(25);
    drive_controller.moveDistanceAsync(42_in);
    drive_controller.waitUntilSettled();
    intake.move(0);
    indexer.move(0);
    drive_controller.moveDistance(-6.5_in);
    drive_controller.waitUntilSettled();   
    drive_controller.turnAngle(70_deg);
    pros::Task::delay(50);
    drive_controller.waitUntilSettled();
    leftF.move(107);
    leftB.move(107);
    rightF.move(103);
    rightB.move(103);
    pros::Task::delay(1250);
    leftF.move(-5);
    leftB.move(-5);
    rightF.move(-5);
    rightB.move(-5);
}


/**
 * 
 * to use functions from the Drive dr, use the following notation. ask rithvik if it doens't work
 * drA->functionName();
 **/
void autonomous() {
        switch (0) {
        case 0: redFront();
        break;
        case 1: blueFront();
        break;
        case 2: redBack();
        break;
        case 3: blueBack();
        break;
    }

}
