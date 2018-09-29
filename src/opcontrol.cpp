#include "main.h"
#include "math.h"

pros::Motor leftFront(5, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(3, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(6, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flipper(7, pros::E_MOTOR_ENCODER_DEGREES);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

bool isIntaking = false;
bool isOuttaking = false;
bool isFlying = false;
bool isDown = false;

int driveCurve(int init) {
  double curve = init/127.0;
  int power = (int) pow(curve,2)*127;
}

void drive(void *param){   
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(true){
          int left = driveCurve(master.get_analog(ANALOG_LEFT_Y));
          int right = driveCurve(master.get_analog(ANALOG_RIGHT_Y));
          leftFront = left;
          leftBack = left;
          rightFront = -right;
          rightBack = -right;
      
    
        /**
        //arcade turns assigned to right joystick (left / right)	
        if(master.get_analog(ANALOG_RIGHT_X) < 0){
            rightFront = master.get_analog(ANALOG_RIGHT_X);
            rightBack = master.get_analog(ANALOG_RIGHT_X);
            leftFront = master.get_analog((ANALOG_RIGHT_X)) * -1;
            leftBack = master.get_analog((ANALOG_RIGHT_X)) * -1;
        } 	else if(master.get_analog(ANALOG_RIGHT_X) > 0){
            rightFront = master.get_analog(ANALOG_RIGHT_X) * -1;
            rightBack = master.get_analog(ANALOG_RIGHT_X) * -1;
            leftFront = master.get_analog((ANALOG_RIGHT_X));
            leftBack = master.get_analog((ANALOG_RIGHT_X));
        }
        */
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
      flywheel.move(-127);
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == 1){
        isFlying = !isFlying;
        flywheel.move(0);
        pros::Task::delay(200);
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
      pros::Task::delay(10);
    }
  }
}


void intakeTask(void* param){
  while (true){
  pros::Controller master(pros::E_CONTROLLER_MASTER);
    while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1){
      intake.move(127);
      pros::Task::delay(10);
      isOuttaking = false;
    }
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1){
      intake.move(-127);
      pros::Task::delay(10);
      isOuttaking = false;
    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X) == 1){
      isOuttaking = !isOuttaking;
      pros::Task::delay(200);
    }
    else{
      pros::Task::delay(10);
    }
    if (!isIntaking){
      intake.move(0);
    }
    if (isOuttaking){
      intake.move(-127);
    }
    pros::Task::delay(10);    
  }
}       

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
	pros::Task startIntake(intakeTask);
  pros::Task startFlipper(flipperTask);
}
