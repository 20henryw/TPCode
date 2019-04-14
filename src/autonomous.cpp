#include "main.h"
using namespace pros;

Drive *drA = new Drive();
Peripherals *peA = new Peripherals();

const int PID_VEL = 127;

const double midTurn = .12;               //turn from platform to face mid post !! THIS NEEDS TO BE CHANGED !!
const double farTurn = .68;               //turn from platform to face oppo color post
const double leftAngTurn = .84;          // left turn, neg. go clockwise
const double leftAngTurnt = .82;          // left turn, neg. go clockwise
const double rightAngTurn = -leftAngTurn; //right turn, positive turns counterclockwise

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

void blueBack()
{
  peA->moveFly(30);
  pros::lcd::set_text(0,"start move");
  drA->pidTurn(3.2, 100);
  drA->waitForStop();
  drA->pidMoveAll(1.5, 100);
  drA->pidMoveLeft(1, 100);
  drA->pidMoveRight(1, 100);
}


/**
 * 
 * to use functions from the Drive dr, use the following notation. ask rithvik if it doens't work
 * drA->functionName();
 **/
void autonomous()
{
  drA->reset(); 
  //pros::Task startDriveAuton(PIDDrive);
  //pros::Task startTurnAuton(turnTask);
  switch (0)
  {
  case 0:
    blueBack();
    break;
  }
  //startDriveAuton.stop(); 
  //startTurnAuton.stop(); 
  drA->reset(); 
}
