#include "main.h"
#include "math.h"

using namespace pros;

bool intMoving = false;
bool indMoving = false;
bool isShooting = false;
bool isFlying = true;

int normPow = 110;
int backPow = 99;
int dShotPow = 50;
int brakePow = -45;

bool isMaxFly = false;
bool dShot = false;
bool dShot2 = false;
bool isUp = true;
bool isDown = false;

Drive *drOp = new Drive();
Peripherals *peOp = new Peripherals();
std::uint8_t lsPort = 2; //limitswitch port
ADIPort ls (lsPort, E_ADI_DIGITAL_IN); //limitswitch

#define max(a, b) \
  ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
  ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

void drive(void *param)
{
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  while (true)
  {
    int left = master.get_analog(ANALOG_LEFT_Y);
    int right = master.get_analog(ANALOG_RIGHT_Y);

    drOp->moveLeft(left);
    drOp->moveRight(right);
    pros::Task::delay(10);
  }  
  /*int prevForward = 0;
  int prevTurn = 0;
  while (true)
  {
    int forward = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);

    if (prevForward != forward || prevTurn != turn || forward != 0 || turn != 0)
    {
      drOp->moveLeft(max(-127, min(127, forward + turn)));
      drOp->moveRight(max(-127, min(127, forward - turn)));
    }

    prevForward = forward;
    prevTurn = turn;

    pros::Task::delay(20);
  }*/
}

void flywheel(void *param)
{
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  int flyPow = normPow;
  while (true)
  {

    
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == 1)
    {
      flyPow = normPow;
      isFlying = !isFlying;
      pros::Task::delay(200);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == 1)
    {
      flyPow = backPow;
      isFlying = !isFlying;
      pros::Task::delay(200);

    }
    else
    {
      pros::Task::delay(10);
    }


    while (isFlying)
    {
      pros::lcd::set_text(4, std::to_string(flyPow));
      peOp->moveFly(flyPow);
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == 1)
      {
        isFlying = !isFlying;
        flyPow = normPow;
        peOp->moveFly(0);
        pros::Task::delay(200);
      }
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == 1)
      {
        if (flyPow == normPow)
        {
          flyPow = backPow;
        }
        else
        {
          flyPow = normPow;
        }
        pros::Task::delay(200);
      }
      pros::Task::delay(10);
    }
    pros::Task::delay(10);
  }
}

/*
void doubleShot()
{
  while (std::abs(peOp->getTopVel()) > 530)
  {
    peOp->moveInt(80);
    peOp->moveInd(100);
  }
  peOp->moveFly(brakePow);
  pros::Task::delay(100);
  peOp->moveFly(dShotPow);
  pros::Task::delay(700);
  peOp->moveInt(0);
  peOp->moveInd(0);
} */

void doubleShotHW()
{
  while (std::abs(peOp->getTopVel()) > 530)
  {
    peOp->moveInt(100);
    peOp->moveInd(80);
  }
  peOp->moveScr(-80);
  peOp->moveInt(0);
  peOp->moveInd(0);
  pros::Task::delay(500);
}

void indexer(void *param)
{
  while (true)
  {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1)
    {
      indMoving = true;
      dShot2 = false;
      peOp->moveInd(80);
      peOp->moveInt(80);
      
      pros::lcd::set_text(5, "L1");
    }
    while (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) == 1)
    {
      int prevVal = ls.get_value();
      bool l2 = true;
      indMoving = true;
      peOp->moveInd(127);
      peOp->moveInt(127);


      while(prevVal == ls.get_value() || ls.get_value() == 1 )
      {
        prevVal = ls.get_value();
        Task::delay(5);
      }

      printf("toggle");

      dShot2 = true;

      peOp->moveScr(127);
      Task::delay(400);

      peOp->resetScr();
      pros::lcd::set_text(5, "L2");
      dShot2 = false;
      Task::delay(5);

    }
    while(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) == 1)
    {
      indMoving = true; 
      peOp->moveInd(-127); 
      pros::Task::delay(10);
    }

    if (indMoving)
    {
      indMoving = false;
      peOp->moveInt(0);
      peOp->moveInd(0); 
    }
    pros::Task::delay(10);
  }
}

void scraper(void *param)
{
  while (true)
  {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
    {
      peOp->moveScr(127);
      isUp = true;
    }
    while (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
      peOp->moveScr(-50);
    }


    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
      peOp->scrBase();
    }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
      peOp->pidAbsScr(0, 127);
      Task::delay(400);
    }    

    if (isUp & !dShot2)
    {
      peOp->scrBrake(pros::E_MOTOR_BRAKE_HOLD);
    }
    else if (!dShot2)
    {
      peOp->scrBrake(pros::E_MOTOR_BRAKE_HOLD);
    }
    
    if(!dShot2)
    {
      //peOp->moveScr(7);
    }
    pros::Task::delay(10);
  }
}

void intake(void *param)
{
  while (true)
  {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1)
    {
      intMoving = true;
      dShot2 = false;
      peOp->moveInt(110);
      peOp->moveInd(0);
      pros::Task::delay(10);
    }
    while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1)
    {
      intMoving = true;
      dShot2 = false;
      peOp->moveInt(-127);
      pros::Task::delay(10);
    }
    if (intMoving)
    {
      intMoving = false;
      peOp->moveInt(0);
    }
     peOp->printFlyPow(1);
    peOp->printFlyVel(2);
    peOp->printFlyTemp(3);
    pros::Task::delay(10);
  }
}

void displayInfo(void *param)
{
  while (true)
  {
    peOp->printFlyPow(1);
    peOp->printFlyVel(2);
    peOp->printFlyTemp(3);
  }
}

/**
 * If no competition control is connected, this function will run immediately
 * following initialize().
 */
void opcontrol()
{
  pros::Task startFly(flywheel);
  pros::Task startDrive(drive);
  pros::Task startIndexer(indexer);
  pros::Task startIntake(intake);
  pros::Task startScraper(scraper);
}
