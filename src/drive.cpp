#include "main.h"
#include "drive.hpp"

#define KF 0
#define KP 0.9f
#define KI 0.0f
#define KD 0.08f

const int LF_PORT = 9;
const int LB_PORT = 10;
const int RF_PORT = 8;
const int RB_PORT = 6;

const pros::motor_gearset_e_t LF_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t LB_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t RF_GEAR = pros::E_MOTOR_GEARSET_18;
const pros::motor_gearset_e_t RB_GEAR = pros::E_MOTOR_GEARSET_18;

const bool LF_REVERSE = false;
const bool LB_REVERSE = false;
const bool RF_REVERSE = true;
const bool RB_REVERSE = true;

static int driveMode = 1;
static int driveTarget = 0;
static int turnTarget = 0;
int maxSpeed = 127;
double pidError = 0.075;
double stopError = 0.15;

double lFTarget = 0;
double lBTarget = 0;
double rFTarget = 0;
double rBTarget = 0;

Drive::Drive() : lFDrive(LF_PORT, LF_GEAR, LF_REVERSE),
                 lBDrive(LB_PORT, LB_GEAR, LB_REVERSE),
                 rFDrive(RF_PORT, RF_GEAR, RF_REVERSE),
                 rBDrive(RB_PORT, RB_GEAR, RB_REVERSE)
{
    pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD);
    lFDrive.set_pos_pid(pid);
    lBDrive.set_pos_pid(pid);
    rFDrive.set_pos_pid(pid);
    rBDrive.set_pos_pid(pid);

    lFDrive.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    lBDrive.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    rFDrive.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    rBDrive.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
}

void Drive::setSpeed(int speed)
{
    maxSpeed = speed;
}

void Drive::tareMotors()
{
    lFDrive.tare_position();
    lBDrive.tare_position();
    rFDrive.tare_position();
    rBDrive.tare_position();
}
void Drive::moveLeft(int power)
{
    lFDrive.move(power);
    lBDrive.move(power);
}

void Drive::moveRight(int power)
{
    rFDrive.move(power);
    rBDrive.move(power);
}

void Drive::moveAll(int power)
{
    moveLeft(power);
    moveRight(power);
}

/* slew control */

const int accel_step = 30;
const int deccel_step = 256; // no decel slew
static int leftSpeed = 0;
static int rightSpeed = 0;

void Drive::leftSlew(int leftTarget)
{
    int step;
    if (abs(leftSpeed) < abs(leftTarget))
        step = accel_step;
    else
        step = deccel_step;

    if (leftTarget > leftSpeed + step)
        leftSpeed += step;
    else if (leftTarget < leftSpeed - step)
        leftSpeed -= step;
    else
        leftSpeed = leftTarget;

    moveLeft(leftSpeed);
}

//slew control
void Drive::rightSlew(int rightTarget)
{
    int step;

    if (abs(rightSpeed) < abs(rightTarget))
        step = accel_step;
    else
        step = deccel_step;

    if (rightTarget > rightSpeed + step)
        rightSpeed += step;
    else if (rightTarget < rightSpeed - step)
        rightSpeed -= step;
    else
        rightSpeed = rightTarget;

    moveRight(rightSpeed);
}

void Drive::reset()
{
    maxSpeed = 127;
    driveTarget = 0;
    lFDrive.tare_position();
    lBDrive.tare_position();
    rFDrive.tare_position();
    rBDrive.tare_position();
    lFTarget = 0;
    lBTarget = 0;
    rFTarget = 0;
    rBTarget = 0;
}

void Drive::PIDDrive(int driveTarget)
{
    int prevError = 0;
    reset();
    while (true)
    {
        pros::Task::delay(10);

        if (driveMode != 1)
            continue;

        int sp = driveTarget;

        double kp = .3;
        double kd = .5;

        //read sensors
        int ls = lFDrive.get_position();
        int rs = rFDrive.get_position();
        int sv = ls;

        //speed
        int error = sp - sv;
        int derivative = error - prevError;
        prevError = error;
        int speed = error * kp + derivative * kd;

        if (speed > maxSpeed)
            speed = maxSpeed;
        if (speed < -maxSpeed)
            speed = -maxSpeed;

        //set motors
        rightSlew(speed);
        leftSlew(speed);
    }
}

void Drive::slowPIDDrive(int driveTarget)
{
    int prevError = 0;
    reset();
    while (true)
    {
        pros::Task::delay(10);

        if (driveMode != 1)
            continue;

        int maxSpeed = 80;

        int sp = driveTarget;

        double kp = .3;
        double kd = .5;

        //read sensors
        int ls = lFDrive.get_position();
        int rs = rFDrive.get_position();
        int sv = ls;

        //speed
        int error = sp - sv;
        int derivative = error - prevError;
        prevError = error;
        int speed = error * kp + derivative * kd;

        if (speed > maxSpeed)
            speed = maxSpeed;
        if (speed < -maxSpeed)
            speed = -maxSpeed;

        //set motors
        rightSlew(speed);
        leftSlew(speed);
    }
}

void Drive::turnTask(void *parameter)
{
    int prevError;

    while (1)
    {
        pros::Task::delay(10);

        if (driveMode != 0)
            continue;

        int sp = turnTarget;

        if (sp > 0)
            sp *= 2.35;
        else
            sp *= 2.3;

        double kp = .9;
        double kd = 3.5;

        int sv = (rFDrive.get_position() - lFDrive.get_position()) / 2;
        int error = sp - sv;
        int derivative = error - prevError;
        prevError = error;
        int speed = error * kp + derivative * kd;

        if (speed > maxSpeed)
            speed = maxSpeed;
        if (speed < -maxSpeed)
            speed = -maxSpeed;

        leftSlew(-speed);
        rightSlew(speed);
    }
}

bool Drive::isDriving()
{
    static int count = 0;
    static int last = 0;
    static int lastTarget = 0;

    int leftPos = lBDrive.get_position();
    int rightPos = rBDrive.get_position();

    int curr = (abs(leftPos) + abs(rightPos)) / 2;
    int thresh = 3;
    int target = turnTarget;

    if (driveMode == 1)
        target = driveTarget;

    if (abs(last - curr) < thresh)
        count++;
    else
        count = 0;

    if (target != lastTarget)
        count = 0;

    lastTarget = target;
    last = curr;

    //not driving if we haven't moved
    if (count > 4)
        return false;
    else
        return true;
}

void Drive::actualDrive(int sp)
{
    reset();
    driveTarget = sp;
    driveMode = 1;
    pros::Task::delay(300);
    while (isDriving())
    {
        pros::Task::delay(450);
    }
}

void Drive::actualTurn(int sp)
{
    reset();
    turnTarget = sp;
    driveMode = 0;
    pros::Task::delay(200);
    while (isDriving())
    {
        pros::Task::delay(20);
    }
}

void Drive::waitForDriveCompletion()
{
    while ((abs(lFDrive.get_position() - lFTarget) +
            abs(lBDrive.get_position() - lBTarget) +
            abs(rFDrive.get_position() - rFTarget) +
            abs(rBDrive.get_position() - rBTarget)) > (pidError * 4))
    {
        pros::lcd::set_text(7, std::to_string(abs(lFDrive.get_position() - lFTarget)));
        pros::Task::delay(5);
    }
}

void Drive::waitForLeftCompletion()
{
    while ((abs(lFDrive.get_position() - lFTarget) +
            abs(lBDrive.get_position() - lBTarget)) > pidError * 2)
    {
        pros::Task::delay(5);
    }
}

void Drive::waitForRightCompletion()
{
    while ((abs(rFDrive.get_position() - rFTarget) +
            abs(rBDrive.get_position() - rBTarget)) > pidError * 2)
    {
        pros::Task::delay(5);
    }
}

void Drive::pidMoveLeft(double position, std::int32_t velocity)
{
    lFTarget += position;
    lBTarget += position;
    lFDrive.move_relative(position, velocity);
    lBDrive.move_relative(position, velocity);
    waitForLeftCompletion();
    pros::Task::delay(50);
}

void Drive::pidMoveRight(double position, std::int32_t velocity)
{
    rFTarget += position;
    rBTarget += position;
    rFDrive.move_relative(position, velocity);
    rBDrive.move_relative(position, velocity);
    waitForRightCompletion();
    pros::Task::delay(50);
}

void Drive::pidMoveAll(double position, std::int32_t velocity)
{
    lFTarget += position;
    lBTarget += position;
    rFTarget += position;
    rBTarget += position;
    lFDrive.move_relative(position, velocity);
    lBDrive.move_relative(position, velocity);
    rFDrive.move_relative(position, velocity);
    rBDrive.move_relative(position, velocity);
    waitForDriveCompletion();
    pros::Task::delay(50);
}

void Drive::pidTurn(double position, std::int32_t velocity)
{
    lFTarget += -position;
    lBTarget += -position;
    rFTarget += position;
    rBTarget += position;
    lFDrive.move_relative(-position, velocity);
    lBDrive.move_relative(-position, velocity);
    rFDrive.move_relative(position, velocity);
    rBDrive.move_relative(position, velocity);
    waitForDriveCompletion();
    pros::Task::delay(50);
}

bool Drive::isStopped()
{
    return (lFDrive.is_stopped() + lBDrive.is_stopped() + rFDrive.is_stopped() + rBDrive.is_stopped()) == 4;
}

void Drive::waitForStop()
{
    pros::lcd::set_text(1, "enter stop wait");
    while ((abs(lFDrive.get_actual_velocity()) +
            abs(lBDrive.get_actual_velocity()) +
            abs(rFDrive.get_actual_velocity()) +
            abs(rBDrive.get_actual_velocity())) > (stopError * 4))
    {
        pros::lcd::set_text(4, std::to_string(lFDrive.get_actual_velocity()));
        pros::lcd::set_text(5, std::to_string(
            (abs(lFDrive.get_actual_velocity()) +
            abs(lBDrive.get_actual_velocity()) +
            abs(rFDrive.get_actual_velocity()) +
            abs(rBDrive.get_actual_velocity()))));
        pros::lcd::set_text(6, std::to_string(pidError * 4));
        pros::Task::delay(5);
    }
    pros::lcd::set_text(7, "exit stop wait");

}