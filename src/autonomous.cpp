#include "main.h"
using namespace okapi;

Drive* drA = new Drive();
Peripherals* peA = new Peripherals();

const int PID_VEL = 120;

const int midTurn = .12; //turn from platform to face mid post !! THIS NEEDS TO BE CHANGED !!
const int farTurn = .68; //turn from platform to face oppo color post
const int rightAngTurn = .77; //right turn, positive turns counterclockwise
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
 * Tune the two back middle autons. Change the midTurn variable. They might also need double shot,
 * which you can copy from the flywheel task in opcontrol. look at drive.cpp and peripherals.cpp
 * for supported functions. to control the drive, use
 * drA->function();
 * to contorl peripherals (flywheel, indexer, intake), use
 * peA->function();
 * text me if you have questions :)) good luck
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
    peA->pidMoveInd(3, 200);
    peA->pidMoveInt(3, 200);
    pros::Task::delay(1500);

    //hit bottom flag, back up
    drA->pidTurn(.16, 100);
    pros::Task::delay(600);
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
    peA->pidMoveInd(3, 200);
    peA->pidMoveInt(3, 200);
    pros::Task::delay(1500);

    //hit bottom flag, back up
    drA->pidTurn(-.16, 100);
    pros::Task::delay(600);
    drA->pidMoveAll(1.7, PID_VEL);
    pros::Task::delay(1000);
    drA->pidMoveAll(-2.2, PID_VEL);
    pros::Task::delay(1000);
    drA->pidTurn(.78, PID_VEL);
}

void redBackMid() {
    //drive forward and intake ball, back up
    peA->moveFly(94);
    peA->moveInt(127);
    peA->moveInd(-110);
    drA->pidMoveAll(3.15, 100);
    pros::Task::delay(2400);
    drA->pidMoveAll(-.63, 100);
    pros::Task::delay(500);
    peA->moveInt(0);
    peA->moveInd(0);


    //turn left, align into parking platform, back up
    drA->pidTurn(rightAngTurn, PID_VEL);
    pros::Task::delay(1000);
    drA->moveAll(60);
    pros::Task::delay(500);
    drA->pidMoveAll(-.2, 100);
    pros::Task::delay(500);

    //move right wheels back to face middle flags
    drA->pidMoveRight(-midTurn, 60);
    pros::Task::delay(5500); // CHANGE DELAY    

    //shoot !! THIS NEEDS TO BE CHANGED !! might need double shot, use timing instead of pid if it's easier
    peA->pidMoveInd(3, 200);
    peA->pidMoveInt(3, 200);
    pros::Task::delay(1500);

    //move right wheels forward to face platform
    drA->pidMoveRight(midTurn, 60);
    pros::Task::delay(1000);

    //park
    drA->pidMoveAll(.18, 100);
    pros::Task::delay(500);
    drA->moveLeft(107);
    drA->moveRight(103);
    pros::Task::delay(1325);
    drA->moveAll(-5);
}


void redBackRight() {
    //drive forward and intake ball, back up
    peA->moveFly(94);
    peA->moveInt(127);
    peA->moveInd(-110);
    drA->pidMoveAll(3.15, 100);
    pros::Task::delay(2400);
    drA->pidMoveAll(-.63, 100);
    pros::Task::delay(500);
    peA->moveInt(0);
    peA->moveInd(0);


    //turn left, align into parking platform, back up
    drA->pidTurn(rightAngTurn, PID_VEL);
    pros::Task::delay(1000);
    drA->moveAll(60);
    pros::Task::delay(500);
    drA->pidMoveAll(-.2, 100);
    pros::Task::delay(500);

    //move right wheels back to face left flags
    drA->pidMoveRight(-farTurn, 60);
    pros::Task::delay(5500); // CHANGE DELAY    

    //shoot
    peA->pidMoveInd(3, 200);
    peA->pidMoveInt(3, 200);
    pros::Task::delay(1500);

    //move right wheels forward to face platform
    drA->pidMoveRight(farTurn, 60);
    pros::Task::delay(1000);

    //park
    drA->pidMoveAll(.18, 100);
    pros::Task::delay(500);
    drA->moveLeft(107);
    drA->moveRight(103);
    pros::Task::delay(1325);
    drA->moveAll(-5);
}


void blueBackMid() {
    //drive forward and intake ball, back up
    peA->moveFly(94);
    peA->moveInt(127);
    peA->moveInd(-110);
    drA->pidMoveAll(3.15, 100);
    pros::Task::delay(2400);
    drA->pidMoveAll(-.63, 100);
    pros::Task::delay(500);
    peA->moveInt(0);
    peA->moveInd(0);


    //turn right, align into parking platform, back up
    drA->pidTurn(-rightAngTurn, PID_VEL);
    pros::Task::delay(1000);
    drA->moveAll(60);
    pros::Task::delay(500);
    drA->pidMoveAll(-.2, 100);
    pros::Task::delay(500);

    //move left wheels back to face middle flags
    drA->pidMoveLeft(-midTurn, 60);
    pros::Task::delay(5500); // CHANGE DELAY    

    //shoot  !! THIS NEEDS TO BE CHANGED !! might need double shot, use timing instead of pid if it's easier
    peA->pidMoveInd(3, 200);
    peA->pidMoveInt(3, 200);
    pros::Task::delay(1500);

    //move left wheels forward to face platform
    drA->pidMoveLeft(midTurn, 60);
    pros::Task::delay(1000);

    //park
    drA->pidMoveAll(.18, 100);
    pros::Task::delay(500);
    drA->moveLeft(107);
    drA->moveRight(103);
    pros::Task::delay(1325);
    drA->moveAll(-5);
}


void blueBackLeft() {
    //drive forward and intake ball, back up
    peA->moveFly(94);
    peA->moveInt(127);
    peA->moveInd(-110);
    drA->pidMoveAll(3.15, 100);
    pros::Task::delay(2400);
    drA->pidMoveAll(-.63, 100);
    pros::Task::delay(500);
    peA->moveInt(0);
    peA->moveInd(0);


    //turn right, align into parking platform, back up
    drA->pidTurn(-rightAngTurn, PID_VEL);
    pros::Task::delay(1000);
    drA->moveAll(60);
    pros::Task::delay(500);
    drA->pidMoveAll(-.2, 100);
    pros::Task::delay(500);

    //move left wheels back to face left flags
    drA->pidMoveLeft(-farTurn, 60);
    pros::Task::delay(5500); // CHANGE DELAY    

    //shoot
    peA->pidMoveInd(3, 200);
    peA->pidMoveInt(3, 200);
    pros::Task::delay(1500);

    //move left wheels forward to face platform
    drA->pidMoveLeft(farTurn, 60);
    pros::Task::delay(1000);

    //park
    drA->pidMoveAll(.18, 100);
    pros::Task::delay(500);
    drA->moveLeft(107);
    drA->moveRight(103);
    pros::Task::delay(1325);
    drA->moveAll(-5);
}

/**
 * 
 * to use functions from the Drive dr, use the following notation. ask rithvik if it doens't work
 * drA->functionName();
 **/
void autonomous() {
        switch (4) {
        case 0: redFront();
        break;
        case 1: blueFront();
        break;
        case 2: redBackMid();
        break;
        case 3: redBackRight();
        break;
        case 4: blueBackMid();
        break;
        case 5: blueBackLeft();
        break;
    }

}
