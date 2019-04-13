#include "main.h"
using namespace okapi;

Drive *drA = new Drive();
Peripherals *peA = new Peripherals();

const int PID_VEL = 120;

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

/**
 * Tune the two back middle autons. Change the midTurn variable. They might also need double shot,
 * which you can copy from the flywheel task in opcontrol. look at drive.cpp and peripherals.cpp
 * for supported functions. to control the drive, use
 * drA->function();
 * to contorl peripherals (flywheel, indexer, intake), use
 * peA->function();
 * text me if you have questions :)) good luck 
 * 
 * ps if the turns don't mirror properly for both sides lmk
 * you can change the pidMoveLeft and pidMoveRight functions to use hardcoded values (.12) instead
 * of the variable name (midTurn). hopefully it'll mirror properly and you won't have to do this.
 */

void autonDS()
{
  while (std::abs(peA->getTopVel()) > 500)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  peA->moveFly(-5);
  pros::Task::delay(100);
  peA->moveFly(125);
  pros::Task::delay(500);
}

void autonDSH()
{
  peA->moveScr(-30);
  pros::Task::delay(70);
  while (std::abs(peA->getTopVel()) > 440)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  pros::Task::delay(150);
  peA->moveScr(-30);
  pros::Task::delay(100);
  peA->moveInt(127);
  peA->moveInd(127);
}

void autonDSS()
{
  while (std::abs(peA->getTopVel()) > 450)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  peA->moveFly(-1);
  pros::Task::delay(100);
  peA->moveFly(127);
  pros::Task::delay(700);
}


void autonDSS2()
{
  while (std::abs(peA->getTopVel()) > 420)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  peA->moveFly(0);
  pros::Task::delay(100);
  peA->moveFly(127);
  pros::Task::delay(700);
}

void autonDS4()
{
  while (std::abs(peA->getTopVel()) > 450)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  peA->moveFly(-40);
  pros::Task::delay(100);
  peA->moveFly(65);
  pros::Task::delay(700);
}



void autonDS2()
{
  while (std::abs(peA->getTopVel()) > 450)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  peA->moveFly(-25);
  pros::Task::delay(110);
  peA->moveFly(94);
  pros::Task::delay(700);
}

void autonDS3()
{
  while (std::abs(peA->getTopVel()) > 450)
  {
    peA->moveInt(127);
    peA->moveInd(127);
  }
  peA->moveFly(-18.5);
  pros::Task::delay(110);
  peA->moveFly(91.5);
  pros::Task::delay(700);
}

void autonDSHW() 
{
    while (std::abs(peA->getTopVel()) > 460)
    {
      peA->moveInt(80);
      peA->moveInd(110);
    }
    peA->moveScr(-70);
    peA->moveInt(0);
    peA->moveInd(0);
    pros::Task::delay(700);


}

void redFront() // 4th dot 
{
  peA->moveFly(100);
  peA->moveInt(127);
  peA->moveScr(40);
  //intake bal
  drA->pidMoveAll(2.9, 100);
  pros::Task::delay(2400);
  //align with wall
  peA->moveInt(100);
  drA->pidMoveAll(-3.4, 115);
  pros::Task::delay(2400);
  peA->moveInt(40);
  drA->pidMoveAll(-.6, 45);
  pros::Task::delay(600);
  //move forward, turn left, shoot
  drA->pidMoveAll(.4, 60);
  pros::Task::delay(1000);
  // turn to face flags
  drA->pidTurn(.71, PID_VEL);
  pros::Task::delay(900);
  drA->pidMoveAll(.43, 80);
  pros::Task::delay(1000);
  // double shot fire
  autonDSHW();
  pros::Task::delay(2000);
  //hit bottom flag, back up
    peA->moveScr(0);
  drA->pidTurn(.045, PID_VEL);
  pros::Task::delay(100);
  peA->moveFly(0);
  peA->moveInt(0);
  peA->moveInd(0);
  drA->pidMoveAll(3.8, 127);
  pros::Task::delay(3000);
  drA->pidMoveAll(-3.0, 100);
  pros::Task::delay(2000);
  drA->pidTurn(rightAngTurn, PID_VEL);
  pros::Task::delay(3600);
  drA->pidMoveAll(.99, 127);
  pros::Task::delay(1000);
}

void blueFront()
{
  peA->moveFly(100);
  peA->moveInt(127);
  peA->moveScr(40);
  //intake ball
  drA->pidMoveAll(3, 100);
  pros::Task::delay(2400);
  //align with wall
  drA->pidMoveAll(-3.4, 115);
  pros::Task::delay(2400);
  peA->moveInt(50);
  drA->pidMoveAll(-.5, 40);
  pros::Task::delay(600);
  //move forward, turn left, shoot
  drA->pidMoveAll(.3, 60);
  pros::Task::delay(1000);
  // turn to face flags
  drA->pidTurn(-.65, PID_VEL);
  pros::Task::delay(900);
  drA->pidMoveAll(.5, 80);
  pros::Task::delay(1000);
  // double shot fire
  autonDSHW();
  pros::Task::delay(1400);
  //hit bottom flag, back up
    peA->moveScr(0);
  drA->pidTurn(-.04, PID_VEL);
  pros::Task::delay(100);
  peA->moveFly(0);
  peA->moveInt(0);
  peA->moveInd(0);
  drA->pidMoveAll(2.9, 127);
  pros::Task::delay(3000);
  drA->pidMoveAll(-2.8, 100);
  pros::Task::delay(2000);
  drA->pidTurn(.87, PID_VEL);
  pros::Task::delay(3600);
  drA->pidMoveAll(.99, 127);
  pros::Task::delay(1000);
}

void redBackMid()
{
  //drive forward and intake ball, back up
  peA->moveFly(108);
  peA->moveInt(127);
  peA->moveScr(70);
  drA->pidMoveAll(3, 100);
  pros::Task::delay(2400);
  drA->pidMoveAll(-.66, 100);
  pros::Task::delay(500);
  peA->moveScr(40);
  peA->moveInt(0);

  //turn left, align into parking platform, back up
  drA->pidTurn(leftAngTurn, PID_VEL);
  pros::Task::delay(1100);

  drA->moveAll(48);
  pros::Task::delay(580);
  drA->pidMoveAll(-.18, 100);
  peA->moveInt(0);
  peA->moveScr(40);

  pros::Task::delay(700);

  //move left wheels back to face left flags
  drA->pidMoveRight(-.616, 60);
  pros::Task::delay(3000); // CHANGE DELAY

  //shoot
  autonDS();
  pros::Task::delay(700);
  peA->moveScr(40);
  peA->moveInt(0);
  peA->moveInd(0);

  //move left wheels forward to face platform
  drA->pidMoveRight(.62, 60);
  pros::Task::delay(1000);

  //park
  drA->pidMoveAll(.10, 90);
  pros::Task::delay(500);
  drA->moveLeft(98);
  drA->moveRight(94);
  peA->moveScr(40);

  pros::Task::delay(1000);
  drA->moveAll(-3);
}

void blueBackMid()
{
  //drive forward and intake ball, back up
  peA->moveFly(95);
  peA->moveInt(127);
  peA->moveScr(70);
  drA->pidMoveAll(3, 100);
  pros::Task::delay(2400);
  drA->pidMoveAll(-.65, 100);
  pros::Task::delay(500);
  peA->moveScr(40);
  peA->moveInt(100);

  //turn left, align into parking platform, back up
  drA->pidTurn(-.855, PID_VEL);
  pros::Task::delay(1100);

  drA->moveAll(50);
  pros::Task::delay(580);
  drA->pidMoveAll(-.18, 100);
  peA->moveInt(0);
  peA->moveScr(40);

  pros::Task::delay(700);

  //move left wheels back to face left flags
  drA->pidMoveLeft(-.065, 60);
  pros::Task::delay(3000); // CHANGE DELAY d

  //shoot
  autonDS3();
  pros::Task::delay(700);
  peA->moveScr(40);
  peA->moveInt(0);
  peA->moveInd(0);

  //move left wheels forward to face platform
  drA->pidMoveLeft(.62, 60);
  pros::Task::delay(1000);

  //park
  drA->pidMoveAll(.10, 90);
  pros::Task::delay(500);
  drA->moveLeft(102);
  drA->moveRight(98);
  peA->moveScr(40);

  pros::Task::delay(1000);
  drA->moveAll(-3);
}

void redBackRight() //4th dot
{
  //drive forward and intake ball, back up
  peA->moveFly(97);
  peA->moveInt(127);
  peA->moveScr(70);
  drA->pidMoveAll(2.67, 100);
  pros::Task::delay(2300);
  drA->pidMoveAll(-.35, 105);
  pros::Task::delay(600);
  peA->moveScr(40);
  //turn left, align into parking platform, back up
  drA->pidTurn(.72, PID_VEL);
  pros::Task::delay(1400);
  peA->moveInt(0);
  drA->moveAll(45);
  pros::Task::delay(700);
  drA->pidMoveAll(-.14, 100);
  peA->moveInt(0);
  peA->moveScr(40);

  pros::Task::delay(700);

  //move right wheels back to face left flags
  drA->pidMoveRight(-.64, 55);
  pros::Task::delay(3700); // CHANGE DELAY

  //shoot
  autonDSS2();
  pros::Task::delay(850);
  peA->moveScr(40);
  peA->moveInt(0);
  peA->moveInd(0);

  //move left wheels forward to face platform
  drA->pidMoveRight(.64, 60);
  pros::Task::delay(1000);

  //park
  drA->pidMoveAll(.11, 90);
  pros::Task::delay(500);
  drA->moveLeft(106);
  drA->moveRight(102);
  peA->moveScr(40);

  pros::Task::delay(1000);
  drA->moveAll(-3);
}

void blueBackLeft() // ALIGN TO 5th dot
{
  //drive forward and intake ball, back up
  peA->moveFly(101.5);
  peA->moveInt(127);
  peA->moveScr(70);
  drA->pidMoveAll(2.8, 100);
  pros::Task::delay(2400);
  drA->pidMoveAll(-.645, 100);
  pros::Task::delay(500);
  peA->moveScr(40);
  peA->moveInt(127);

  //turn right, align into parking platform, back up
  drA->pidTurn(-.87, PID_VEL);
  pros::Task::delay(1100);
  peA->moveInt(0);
  drA->moveAll(52);
  pros::Task::delay(700);
  drA->pidMoveAll(-.18, 100);
  peA->moveInt(0);
  peA->moveScr(40);

  pros::Task::delay(700);

  //move left wheels back to face left flags
  drA->pidMoveLeft(-.587, 60);
  pros::Task::delay(4000); // CHANGE DELAY d

  //shoot
  autonDSS();
  pros::Task::delay(700);
  peA->moveScr(40);
  peA->moveInt(0);
  peA->moveInd(0);

  //move left wheels forward to face platform
  drA->pidMoveLeft(.62, 60);
  pros::Task::delay(1000);

  //park
  drA->pidMoveAll(.10, 80);
  pros::Task::delay(500);
  drA->moveLeft(100);
  drA->moveRight(98);
  peA->moveScr(40);
  pros::Task::delay(1000);
  drA->moveAll(-3);
}

void simpleSkills()
{
  peA->moveFly(104);
  peA->moveInt(127);

  drA->pidMoveAll(3.15, 105);
  pros::Task::delay(2300);
  //bump into wall
  drA->pidMoveAll(-3.5, 110);
  pros::Task::delay(2500);
  drA->pidMoveAll(-.24, 40);
  pros::Task::delay(600);
  drA->pidMoveAll(.39, 60);
  pros::Task::delay(1000);
  drA->pidTurn(.795, 100);
  pros::Task::delay(900);
  drA->pidMoveAll(3.21, 100);
  pros::Task::delay(2700);
  //fire
  autonDS();
  pros::Task::delay(500);

  peA->moveInt(0);
  peA->moveInd(0);
  peA->moveFly(104.5);
  peA->moveInt(127);
  //turn to face bottom flag
  drA->pidTurn(.03, PID_VEL);
  pros::Task::delay(800);
  drA->pidMoveAll(4.06, 100);
  // hit bottom flag
  pros::Task::delay(4800);
  drA->pidMoveAll(-3.4, 100);
  pros::Task::delay(2600);
  drA->pidTurn(rightAngTurn, PID_VEL);

  pros::Task::delay(900);
  //back upinto wall
  drA->pidMoveAll(-.6, 70);
  pros::Task::delay(700);
  drA->pidMoveAll(3.15, 100);
  pros::Task::delay(2350);
  // fire again at the two center flags - hopefully gets two
  drA->pidTurn(.605, PID_VEL);
  pros::Task::delay(3000);
  autonDS();
  pros::Task::delay(400);
  drA->pidMoveAll(.3, 100);
  pros::Task::delay(1000);
  // drive forward to turn around to park

  drA->pidTurn(-.605, PID_VEL);
  pros::Task::delay(1800);

  // back up into wall
  drA->pidMoveAll(-3.2, 110);
  pros::Task::delay(2700);
  drA->pidMoveAll(-.27, 40);
  pros::Task::delay(700);
  drA->pidMoveAll(.39, 60);
  pros::Task::delay(1000);
  drA->pidTurn(-.78, PID_VEL);
  pros::Task::delay(900);
  drA->pidMoveAll(2.21, 60);
  pros::Task::delay(3200);
  drA->pidTurn(leftAngTurn, PID_VEL);

  pros::Task::delay(900);
  drA->pidMoveAll(-.3, 40);
  pros::Task::delay(700);
  drA->pidMoveAll(.5, 40);
  pros::Task::delay(1000);
  drA->moveLeft(110);
  drA->moveRight(108);
  pros::Task::delay(2900);
  drA->moveLeft(-2);
  drA->moveRight(-2);

  /*rA->pidTurn(1.799, 100);
  pros::Task::delay(1300);
  drA->pidMoveAll(.63, 127);
  pros::Task::delay(1000);
  drA->moveLeft(100);
  drA->moveRight(100);
  pros::Task::delay(1100);
  //face top platform
  drA->pidTurn(leftAngTurn, PID_VEL);
  pros::Task::delay(1000);
  drA->moveLeft(80);
  drA->moveRight(80);
  pros::Task::delay(150);*/
}

void test()
{
  drA->pidTurn(1.62, 100);
  pros::Task::delay(1300);
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
  switch (5)
  {
  case 0:
    redFront();
    break;
  case 1:
    blueFront();
    break;
  case 2:
    redBackMid();
    break;
  case 3:
    redBackRight();
    break;
  case 4:
    blueBackMid();
    break;
  case 5:
    blueBackLeft();
    break;
  case 6:
    simpleSkills();
    break;
  }
  //startDriveAuton.stop(); 
  //startTurnAuton.stop(); 
  drA->reset(); 
}
