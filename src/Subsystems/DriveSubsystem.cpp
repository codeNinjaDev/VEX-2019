#include "User/DriveSubsystem.h"
#include <cmath>
#include "User/Constants.h"

// Set drivetrain with reversed left side, green gearset, wheel diameter, TRACK_WIDTH
// Set Encoder ports
DriveSubsystem::DriveSubsystem(okapi::Controller iDriverController) : driverController(iDriverController)
  , driveTrain(okapi::ChassisControllerFactory::create({-BACK_LEFT_MOTOR_PORT,-FRONT_LEFT_MOTOR_PORT}
    ,  {BACK_RIGHT_MOTOR_PORT, FRONT_RIGHT_MOTOR_PORT}
    , okapi::AbstractMotor::gearset::green, {BACK_WHEEL_DIAMETER, TRACK_WIDTH}))
{
  // Set current state to initialize state
  m_stateVal = DriveState::kInitialize;
}


void DriveSubsystem::initialize() {
  reset();
}

void DriveSubsystem::reset() {
  // Reset sensors and stop all drive motors
  driveTrain.resetSensors();
  stop();
}

void DriveSubsystem::stop() {
  driveTrain.stop();
}

void DriveSubsystem::update() {

  switch (m_stateVal) {
    case (DriveState::kInitialize):
      /*
       If current state is kInitialize,
       run the initialize function and set the next state to be teleop
       */
      initialize();
      nextState = DriveState::kTeleopDrive;
      break;
    case (DriveState::kTeleopDrive):
    /*
     If current state is kTeleopDrive,
     run the drive train
     */
      if (true) {
        arcadeDrive(-driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , -driverController.getAnalog(okapi::ControllerAnalog::rightX)
          , true);

          std::printf("%f", -driverController.getAnalog(okapi::ControllerAnalog::leftY));
      } else {
        tankDrive(-driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , -driverController.getAnalog(okapi::ControllerAnalog::rightY)
          , true);
      }
      break;
  }

  // Set current state to next state
  m_stateVal = nextState;
}

void DriveSubsystem::arcadeDrive(double forward, double rotate, bool teleOp) {
  if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
    driveTrain.arcade(squareInput(forward), squareInput(rotate));
  } else {
    driveTrain.arcade(forward, rotate);
  }
}

void DriveSubsystem::tankDrive(double myLeft, double myRight, bool teleOp) {
  if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
    driveTrain.tank(squareInput(myLeft), squareInput(myRight));
  } else {
    driveTrain.tank(myLeft, myRight);
  }
}
double DriveSubsystem::getLeftEncoder() {
  return EncoderUtil::getInches(driveTrain.getSensorVals()[0], BACK_WHEEL_DIAMETER);
}

double DriveSubsystem::getRightEncoder() {
  return EncoderUtil::getInches(driveTrain.getSensorVals()[1], BACK_WHEEL_DIAMETER);
}

double DriveSubsystem::squareInput(double input) {
  // Keeps the original sign, but squares the magnitude.
  return copysign(pow(input, 2), input);
}
