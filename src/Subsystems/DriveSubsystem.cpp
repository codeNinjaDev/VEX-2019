#include "User/DriveSubsystem.h"
#include <cmath>
#include "User/Constants.h"

DriveSubsystem::DriveSubsystem(okapi::Controller iDriverController) : driverController(iDriverController)
  , driveTrain(okapi::ChassisControllerFactory::create({-BACK_LEFT_MOTOR_PORT,-FRONT_LEFT_MOTOR_PORT}
    ,  {BACK_RIGHT_MOTOR_PORT, FRONT_RIGHT_MOTOR_PORT}
    , okapi::AbstractMotor::gearset::green, {BACK_WHEEL_DIAMETER, TRACK_WIDTH}))
  , leftEncoder(LEFT_TOP_ENCODER_PORT, LEFT_BOTTOM_ENCODER_PORT, FRONT_WHEEL_DIAMETER, false)
  , rightEncoder(LEFT_TOP_ENCODER_PORT, LEFT_BOTTOM_ENCODER_PORT, FRONT_WHEEL_DIAMETER, false)
{
  m_stateVal = DriveState::kInitialize;
}


void DriveSubsystem::initialize() {
  reset();
}

void DriveSubsystem::reset() {
  leftEncoder.reset();
  rightEncoder.reset();
  driveTrain.resetSensors();
  stop();
}

void DriveSubsystem::stop() {
  driveTrain.stop();
}

void DriveSubsystem::update() {
  switch (m_stateVal) {
    case (DriveState::kInitialize):
      initialize();
      nextState = DriveState::kTeleopDrive;
      break;
    case (DriveState::kTeleopDrive):
      if (ARCADE_DRIVE) {
        ArcadeDrive(driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , driverController.getAnalog(okapi::ControllerAnalog::rightX)
          , true);
      } else {
        TankDrive(driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , -driverController.getAnalog(okapi::ControllerAnalog::rightY)
          , true);
      }
      break;
  }

  m_stateVal = nextState;
}

void DriveSubsystem::ArcadeDrive(double forward, double rotate, bool teleOp) {
  if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
    driveTrain.arcade(copysign(pow(forward, 2), forward), copysign(pow(rotate, 2), rotate));
  } else {
    driveTrain.arcade(forward, rotate);
  }
}

void DriveSubsystem::TankDrive(double myLeft, double myRight, bool teleOp) {
  if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
    driveTrain.tank(copysign(pow(myLeft, 2), myLeft), copysign(pow(myRight, 2), myRight));
  } else {
    driveTrain.tank(myLeft, myRight);
  }
}
double DriveSubsystem::getLeftEncoder() {
  return leftEncoder.getInches();
}

double DriveSubsystem::getRightEncoder() {
  return rightEncoder.getInches();
}
