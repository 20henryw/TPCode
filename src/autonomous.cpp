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

std::uint8_t lsAPort = 2; //limitswitch port
ADIPort lsA (lsAPort, E_ADI_DIGITAL_IN); //limitswitch


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

void dS()
{
  int prevVal = lsA.get_value();
  bool l2 = true;
  peA->moveInd(127);
  peA->moveInt(127);
  lcd::set_text(1, "ds");

  while(prevVal == lsA.get_value() || lsA.get_value() == 1 )
    {
      prevVal = lsA.get_value();
      Task::delay(5);
    }

  peA->moveScr(127);
  Task::delay(200);
  peA->resetScr();
  peA->moveInd(0);
  peA->moveInt(0);
}

void shoot()
{
  peA->moveInd(127);
  peA->moveInt(127);
  Task::delay(200);
  peA->moveInd(127);
  peA->moveInt(127);

}

void shootMid()
{
  int prevVal = lsA.get_value();
  bool l2 = true;
  peA->moveInd(127);
  peA->moveInt(127);
  lcd::set_text(1, "ds");

  while(prevVal == lsA.get_value() || lsA.get_value() == 1 )
    {
      prevVal = lsA.get_value();
      Task::delay(5);
    }

  peA->moveInd(100);
  peA->moveInt(100);
  peA->moveFly(125);
  Task::delay(200);
  peA->moveInd(0);
  peA->moveInt(127);
}

void shootFar()
{
  int prevVal = lsA.get_value();
  bool l2 = true;
  peA->moveInd(127);
  peA->moveInt(127);
  lcd::set_text(1, "ds");

  while(prevVal == lsA.get_value() || lsA.get_value() == 1 )
    {
      prevVal = lsA.get_value();
      Task::delay(5);
    }

  peA->moveInd(100);
  peA->moveInt(100);
  peA->moveFly(125);
  Task::delay(200);
  peA->moveInd(0);
  peA->moveInt(0);
}

void blueBack()
{
  pros::lcd::set_text(0,"start move");
  drA->pidTurn(3.12, 100);
  drA->waitForStop();

}

void redFrontSideMid()
{

  //drive forward, pickup ball
  peA->moveFly(110);
  peA->moveInt(100);
  peA->scrBase();
  drA->pidMoveAll(3.18 , PID_VEL);
  drA->waitForStop();

  //back up, align with wall
  peA->pidAbsScr(0, 100);
  drA->pidMoveAll(-3.03, PID_VEL);
  drA->moveAll(-90);
  Task::delay(300);
  drA->reset();

  //drive forward, turn right to face side flags
  peA->moveInt(80);
  lcd::set_text(0, "start moving forward");
  drA->pidMoveAll(.2, 127);
  lcd::set_text(7, "done moving forward");
  drA->pidTurn(.76, 80);
  drA->waitForStop();
  drA->pidMoveAll(1, 127);
  drA->waitForStop();
  lcd::set_text(0, "start shoot");
  
  //shoot, toggle bottom flag
  dS();
  drA->pidTurn(.04, 127);
  drA->pidMoveAll(2.2, 127);
  peA->pidMoveScr(-.15,127);

}

void blueFrontSideMid()
{

  //drive forward, pickup ball
  peA->moveFly(110);
  peA->moveInt(100);
  peA->scrBase();
  drA->pidMoveAll(3.18 , PID_VEL);
  drA->waitForStop();

  //back up, align with wall
  peA->pidAbsScr(0, 100);
  drA->pidMoveAll(-3.03, PID_VEL);
  drA->moveAll(-90);
  Task::delay(300);
  drA->reset();

  //drive forward, turn right to face side flags
  peA->moveInt(80);
  lcd::set_text(0, "start moving forward");
  drA->pidMoveAll(.2, 127);
  lcd::set_text(7, "done moving forward");
  drA->pidTurn(-.76, 80);
  drA->waitForStop();
  drA->pidMoveAll(1, 127);
  drA->waitForStop();
  lcd::set_text(0, "start shoot");
  
  //shoot, toggle bottom flag
  dS();
  drA->pidTurn(-.08, 127);
  drA->pidMoveAll(2.2, 127);
  peA->pidMoveScr(-.15,127);
}

void redBack()
{

  //drive forward, pickup ball
  peA->moveFly(95);
  peA->moveInt(100);
  peA->tareScr();
  peA->pidAbsScr(0, 127);
  drA->pidMoveAll(3.18 , PID_VEL);
  drA->waitForStop();

  //back up, align with platform
  drA->pidMoveAll(-.25, PID_VEL);
  Task::delay(200);
  peA->moveInt(0);
  // drA->waitForStop();
  drA->pidTurn(.76,80);
  drA->moveAll(70);
  Task::delay(300);
  peA->moveInt(127);
  drA->reset();

  //aim, shoot
  drA->pidMoveAll(-.34, 50);
  drA->waitForStop();
  drA->pidTurn(-.101, 50);
  drA->waitForStop();
  shoot();
  Task::delay(300);

  peA->moveFly(99);
  drA->pidTurn(-1.28, 90);
  Task::delay(400);
  drA->pidMoveAll(1.09, 100);
  drA->pidMoveLeft(.18, PID_VEL);
  drA->waitForStop();
  peA->pidMoveScr(-.18,50);
  
  

}

void redBack2()
{

  //drive forward, pickup ball
  peA->moveFly(99);
  peA->moveInt(0);
  peA->tareScr();
  peA->pidAbsScr(0, 127);
  drA->pidMoveAll(1.75, 120);
  Task::delay(750);

  //Turn, scrape ball
  drA->pidTurn(.76, 80);
  drA->pidMoveAll(.18, 60);
  peA->moveInt(127);
  peA->pidMoveScr(-.235, 127);
  Task::delay(200);
  drA->pidMoveAll(-.05,50);
  peA->moveInt(-80);
  Task::delay(200);
  peA->moveInt(127);
  
  //aim, shoot
  drA->pidMoveAll(-.34, 50);
  drA->waitForStop();
  drA->pidTurn(-.062, 50);
  drA->waitForStop();
  shootMid();
  peA->moveFly(98);
  peA->moveInt(110);
  peA->pidAbsScr(0,70);

  //turn right, intake ball
  drA->pidMoveAll(.85,100);
  Task::delay(500);

  //back up, turn right, scrape ball
  drA->pidMoveAll(-.35, 60);
  Task::delay(300);
  drA->pidTurn(-.61, 50);
  Task::delay(300);
  drA->pidMoveAll(.72, 60);
  peA->pidMoveScr(-.19, 127);
  peA->moveInt(110);
  drA->pidMoveAll(-.32, 50);
  Task::delay(300);
  peA->moveInt(-5);
  Task::delay(100);
  peA->moveInt(127);
  peA->pidAbsScr(0, 127);

  //turn left at far flag, shoot
  drA->pidTurn(1, 80);
  Task::delay(300);
  shootFar();
  drA->pidTurn(.255, 80);
  // drA->moveLeft(127);
  // drA->moveRight(100);
  // Task::delay(1400);
  // drA->moveAll(-10);

}

//shoot mid, flip cap, shoot far
void redBack3()
{

  //drive forward, pickup ball
  peA->moveFly(102);
  peA->moveInt(0);
  peA->moveScr(7);
  drA->pidMoveAll(1.75, 80);
  Task::delay(700);
  peA->tareScr();
  peA->pidAbsScr(0, 127);

  //Turn left, scrape ball
  drA->pidTurn(.7, 80);
  drA->pidMoveAll(.15, 60);
  peA->moveInt(127);
  peA->pidMoveScr(-.235, 100);
  Task::delay(200);
  drA->pidMoveAll(-.02,50);
  peA->moveInt(127);
  
  //aim right, shoot
  drA->pidMoveAll(-.34, 50);
  drA->waitForStop();
  drA->pidTurn(-.026, 50);
  //drA->waitForStop();
  Task::delay(300);
  shootMid();
  peA->moveInt(100);
  peA->moveFly(99);
  peA->pidAbsScr(0,70);

  //turn right, intake ball
  drA->pidTurn(-.693, 50);
  drA->pidMoveAll(.85,100);
  Task::delay(500);

  //back up, turn right, scrape ball
  drA->pidMoveAll(-.35, 60);
  Task::delay(300);
  drA->pidTurn(-.5, 50);
  Task::delay(300);
  drA->pidMoveAll(.64, 60);
  peA->pidMoveScr(-.26, 100);
  Task::delay(300);
  peA->moveInt(100);
  drA->pidMoveAll(-.39, 50);
  Task::delay(800);
  
  //flip cap
  peA->moveInt(0);
  peA->pidAbsScr(-.5, 127);
  drA->pidMoveAll(.39, 60);
  Task::delay(500);
  peA->pidAbsScr(0, 110);
  Task::delay(500);
  peA->moveInt(90);
  drA->pidMoveAll(-.77  , 60);
  Task::delay(300);

  //turn left at far flag, shoot
  drA->pidTurn(.987, 80);
  Task::delay(600);
  shootFar();

}

//shoot mid, flip cap, shoot far
void blueBack3()
{

 //drive forward, pickup ball
  peA->moveFly(102);
  peA->moveInt(0);
  peA->moveScr(7);
  drA->pidMoveAll(1.75, 80);
  Task::delay(700);
  peA->tareScr();
  peA->pidAbsScr(0, 127);

  //Turn right, scrape ball
  drA->pidTurn(-.7, 80);
  drA->pidMoveAll(.15, 60);
  peA->moveInt(127);
  peA->pidMoveScr(-.235, 100);
  Task::delay(200);
  drA->pidMoveAll(-.02,50);
  peA->moveInt(127);
  
  //aim left, shoot
  drA->pidMoveAll(-.34, 50);
  drA->waitForStop();
  drA->pidTurn(.022, 50);
  //drA->waitForStop();
  Task::delay(300);
  shootMid();
  peA->moveInt(110);
  peA->moveFly(99);
  peA->pidAbsScr(0,70);

  //turn left, intake ball
  drA->pidTurn(.696, 50);
  drA->pidMoveAll(.85,100);
  Task::delay(500);

  //back up, turn left, scrape ball
  drA->pidMoveAll(-.35, 60);
  Task::delay(300);
  drA->pidTurn(.5, 50);
  Task::delay(300);
  drA->pidMoveAll(.64, 60);
  peA->pidMoveScr(-.26, 100);
  Task::delay(300);
  peA->moveInt(100);
  drA->pidMoveAll(-.39, 50);
  Task::delay(800);
  
  //flip cap
  peA->moveInt(0);
  peA->pidAbsScr(-.5, 127);
  drA->pidMoveAll(.39, 60);
  Task::delay(500);
  peA->pidAbsScr(0, 110);
  Task::delay(500);
  peA->moveInt(100);
  drA->pidMoveAll(-.77, 60);
  Task::delay(300);

  //turn right at far flag, shoot
  drA->pidTurn(-.967, 80);
  Task::delay(600);
  shootFar();

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
  switch (6)
  {
  case 0:
    redFrontSideMid();
    break;
  case 1:
    blueFrontSideMid();
    break;
  case 2:
    redBack();
    break;
  case 3:
    blueBack();
    break;
  case 4:
    redBack2();
    break;
  case 5:
    redBack3();
    break;
  case 6:
    blueBack3();
    break;
  }
  //startDriveAuton.stop(); 
  //startTurnAuton.stop(); 
  drA->reset(); 
}
