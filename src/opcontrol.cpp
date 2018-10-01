#include "main.h"
#include "math.h"

using namespace okapi;
pros::Motor leftFront(11, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(3, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(2, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(4, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel1(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel2(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(6, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flipper(7, pros::E_MOTOR_ENCODER_DEGREES);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

bool isIntaking = false;
bool isOuttaking = false;
bool isFlying = false;
bool isDown = false;
int flyPow = 127;

int driveCurve(int init) {
  int dir = init/abs(init);
  return ((int) ((pow(init/127.0,2)) * 127 * dir));
  
}

void drive(void *param){   
    Motor leftF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor leftB(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor rightB(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    while(true){
//          int left = driveCurve(master.get_analog(ANALOG_LEFT_Y));
//          int right = driveCurve(master.get_analog(ANALOG_RIGHT_Y));
      float exponent = 2;
      int left = master.get_analog(ANALOG_LEFT_Y);
      //int leftDir = left/abs(left);
      int right = master.get_analog(ANALOG_RIGHT_Y);
      //int rightDir = right/abs(right);

      leftF.move(left);
      leftB.move(left);
      rightF.move(right);
      rightB.move(right);
      
      pros::lcd::set_text(3, std::to_string(leftF.get_temperature()));
      pros::lcd::set_text(4, std::to_string(leftB.get_temperature()));
      pros::lcd::set_text(5, std::to_string(rightF.get_temperature()));
      pros::lcd::set_text(6, std::to_string(rightB.get_temperature()));

      // leftFront = driveCurve(left);
      // leftBack = driveCurve(left);
      // rightFront = -driveCurve(right);
      // rightBack = -driveCurve(right);

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
      flywheel1.move(flyPow);
      flywheel2.move(flyPow);
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == 1){
        isFlying = !isFlying;
        flywheel1.move(0);
        flywheel2.move(0);
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
      pros::lcd::set_text(1, std::to_string(-flywheel1.get_actual_velocity()));
      pros::lcd::set_text(2, std::to_string(-flywheel2.get_actual_velocity()));
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
