#include "User/DriveSubsystem.h"
#include <cmath>
#include "User/Constants.h"

// Set drivetrain with reversed left side, green gearset, wheel diameter, TRACK_WIDTH
// Set Encoder ports
DriveSubsystem::DriveSubsystem(okapi::Controller iDriverController) : driverController(iDriverController)
  , driveTrain(okapi::ChassisControllerFactory::create({-BACK_LEFT_MOTOR_PORT,-FRONT_LEFT_MOTOR_PORT}
    ,  {BACK_RIGHT_MOTOR_PORT, FRONT_RIGHT_MOTOR_PORT}
    , okapi::AbstractMotor::gearset::green, {BACK_WHEEL_DIAMETER, TRACK_WIDTH}))
    , SlowDown1(okapi::ControllerId::master, okapi::ControllerDigital::R2)
    , SlowDown2(okapi::ControllerId::master, okapi::ControllerDigital::L2)
    , toggleDriveButton(okapi::ControllerId::master, okapi::ControllerDigital::right)
    , toggleDefenseButton(okapi::ControllerId::master, okapi::ControllerDigital::X)
{
  // Set current state to initialize state
  toggleDrive = false;
  toggleDefense = false;

  driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
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
      driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

      nextState = DriveState::kTeleopDrive;
      break;
    case (DriveState::kTeleopDrive):
    /*
     If current state is kTeleopDrive,
     run the drive train
     */
      if(toggleDriveButton.changedToPressed()) {
        toggleDrive = !toggleDrive;
        driverController.rumble("..");
      }

      if(toggleDefenseButton.changedToPressed()) {
        toggleDefense = !toggleDefense;
        driverController.rumble("-.");
      }

      if(toggleDefense) {
        driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
      } else {
        driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
      }

      if (toggleDrive) {
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

  double multiplier = 1;

  if (SlowDown1.isPressed() && SlowDown1.isPressed()) {
    multiplier = 0.4;
    driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  } else if (SlowDown1.isPressed() || SlowDown1.isPressed()) {
    multiplier = 0.75;
    driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  } else {
    multiplier = 1;
  }

  if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
    driveTrain.arcade(squareInput(forward) * multiplier, squareInput(rotate) * multiplier);
  } else {
    driveTrain.arcade(forward * multiplier, rotate * multiplier);
  }

}

void DriveSubsystem::tankDrive(double myLeft, double myRight, bool teleOp) {

  double multiplier = 1;
  if (SlowDown1.isPressed() && SlowDown1.isPressed()) {
    multiplier = 0.4;
    driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  } else if (SlowDown1.isPressed() || SlowDown1.isPressed()) {
    multiplier = 0.75;
    driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  } else {
    multiplier = 1;
  }

  if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
    driveTrain.tank(squareInput(myLeft) * multiplier, squareInput(myRight) * multiplier);
  } else {
    driveTrain.tank(myLeft * multiplier, myRight * multiplier);
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

void DriveSubsystem::moveMetersAsync(double meters) {
  driveTrain.moveDistanceAsync(meters * okapi::meter);
}

void DriveSubsystem::moveInchesAsync(double inches) {
  driveTrain.moveDistanceAsync(inches * okapi::inch);
}

void DriveSubsystem::turnDegrees(double angle) {
  driveTrain.turnAngleAsync(angle * okapi::degree);
}
