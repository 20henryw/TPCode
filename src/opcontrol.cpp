#include "main.h"
#include "math.h"

using namespace okapi;

bool intMoving = false;
bool indMoving = false;
bool isShooting = false;
bool isFlying = false;
bool isDown = false;
int flyPow = 104;
int normRot = 520;
int shotSlowRot = 475;
int dShotPow = 75 ;
int brakePow = -20;
bool isMaxFly = false;
bool dShot = false;


Drive* drOp = new Drive();
Peripherals* peOp = new Peripherals();

int driveCurve(int init) {
  int dir = init/abs(init);
  return ((int) ((pow(init/127.0,2)) * 127 * dir));
  
}

void drive(void *param){   
 
    /*
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    */

    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(true){
        int left = master.get_analog(ANALOG_LEFT_Y);
        int right = master.get_analog(ANALOG_RIGHT_Y);
     
        drOp->moveLeft(left);
        drOp->moveRight(right);
        pros::Task::delay(10);
  
    }
}

void flywheelTask(void *param){
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  while(true){
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == 1){
      isFlying = !isFlying;
      pros::Task::delay(200);
    }
    else{
      pros::Task::delay(10);
    }
    while(isFlying){
      peOp->moveFly(flyPow);
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == 1){
        isFlying = !isFlying;
        peOp->moveFly(0);
        pros::Task::delay(200);
      }
      if(std::abs(peOp->getTopVel()) > normRot){
        isMaxFly = true;
      }

      if (isMaxFly && dShot){
        if(std::abs(peOp->getTopVel()) < shotSlowRot){
          isMaxFly = false;
          pros::lcd::set_text(5, "breaking");
          peOp->moveFly(brakePow);
          pros::Task::delay(100);
          peOp->moveFly(dShotPow);
          pros::Task::delay(700);
        }
      }
  
      
      /**
      else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == 1 && isFlying){
        flywheel.move(30);
        pros::Task::delay(100);
        flywheel.move(-83);
        pros::Task::delay(1000);
        isIntaking = true;
        intake.move(127);
        pros::Task::delay(2500);
        isIntaking = false;
        intake.move(0);
      }
      */
      peOp->printFlyVel(1);
      peOp->printFlyTemp(3);
      pros::Task::delay(10);
    }
    peOp->printFlyVel(1);
    peOp->printFlyTemp(3);
  }
}

void indexerTask(void* param) {
  while(true) {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
      indMoving = true;
      dShot = false;
      peOp->moveInd(127);
      peOp->moveInt(127);
      pros::Task::delay(10);
      pros::lcd::set_text(5, "L1");
    }
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1) {
      indMoving = true;
      dShot = true;
      peOp->moveInd(127);
      peOp->moveInt(127);
      pros::Task::delay(10);
      pros::lcd::set_text(5, "L2");
    }
    if (indMoving) {
      indMoving = false;
      peOp->moveInt(0);
    }
    peOp->moveInd(-10);
    pros::Task::delay(10);
  }
}

void intakeTask(void* param){
  while (true){
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1){
      intMoving = true;
      peOp->moveInt(110);
      peOp->moveInd(-127);
      pros::Task::delay(10);
    }
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1){
      intMoving = true;
      peOp->moveInt(-127);
      pros::Task::delay(10);
    }
    if (intMoving) {
      intMoving = false;
      peOp->moveInt(0);
    }
    pros::Task::delay(10);    
  }
}


/*
void flipperTask(void* param){
  while (true){
  pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1){
      flipper.move(127);
      pros::Task::delay(10);
      isDown = false;
    }
    while (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1){
      flipper.move(-127);
      pros::Task::delay(10);
      isDown = true;
    }    
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) == 1){
      flipper.move(127);
      pros::Task::delay(200);
    }
    if (isDown){
      flipper.move(-20);
    }
    else{
      flipper.move(0);
    }
    pros::Task::delay(10);    
  }
}       
*/
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

//task starter function (called by competition)
void opcontrol() {

	pros::Task startFly(flywheelTask);
	pros::Task startDrive(drive);
  pros::Task startIndexer(indexerTask);
	pros::Task startIntake(intakeTask);
  //pros::Task startFlipper(flipperTask);
}
