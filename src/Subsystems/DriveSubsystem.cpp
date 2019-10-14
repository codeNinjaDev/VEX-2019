#include "User/DriveSubsystem.h"
#include <cmath>
#include "User/Constants.h"

// Set drivetrain with reversed left side, green gearset, wheel diameter, TRACK_WIDTH
// Set Encoder ports
DriveSubsystem::DriveSubsystem(okapi::Controller iDriverController) : driverController(iDriverController)
  , backLeftDriveMotor(BACK_LEFT_MOTOR_PORT)
  , backRightDriveMotor(-BACK_RIGHT_MOTOR_PORT)
  , frontLeftDriveMotor(FRONT_LEFT_MOTOR_PORT)
  , frontRightDriveMotor(-FRONT_RIGHT_MOTOR_PORT)
  , leftMotors({backLeftDriveMotor, frontLeftDriveMotor})
  , rightMotors({backRightDriveMotor, frontRightDriveMotor})
  , driveTrain(okapi::ChassisControllerFactory::create(leftMotors,rightMotors, okapi::AbstractMotor::gearset::green, {BACK_WHEEL_DIAMETER, WHEELBASE_WIDTH}))
  , profileController(okapi::AsyncControllerFactory::motionProfile(
      1.0,  // Maximum linear velocity of the Chassis in m/s
      2.0,  // Maximum linear acceleration of the Chassis in m/s/s
      10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      driveTrain // Chassis Controller
    ))
    , SlowDown1(okapi::ControllerId::master, okapi::ControllerDigital::R2)
    , SlowDown2(okapi::ControllerId::master, okapi::ControllerDigital::L2)
    , toggleDriveButton(okapi::ControllerId::master, okapi::ControllerDigital::right)
    , toggleDefenseButton(okapi::ControllerId::master, okapi::ControllerDigital::X)
{
  // Set current state to initialize state
  toggleDrive = false;
  toggleDefense = false;


  driveTrain.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  driveTrain.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

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
  driveTrain.setMaxVelocity(200);
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
        arcadeDrive(driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , -driverController.getAnalog(okapi::ControllerAnalog::rightX)
          , true);

          std::printf("%f", -driverController.getAnalog(okapi::ControllerAnalog::leftY));
      } else {
        tankDrive(driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , driverController.getAnalog(okapi::ControllerAnalog::rightY)
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

  double left = forward + rotate;
  double right = forward - rotate;

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
    leftMotors.controllerSet(squareInput(myLeft) * multiplier);
    rightMotors.controllerSet(squareInput(myRight) * multiplier);
  } else {
    leftMotors.controllerSet(myLeft * multiplier);
    rightMotors.controllerSet(myRight * multiplier);
  }

}

double DriveSubsystem::getLeftEncoder() {
  return EncoderUtil::getInches(driveTrain.getSensorVals()[0], BACK_WHEEL_DIAMETER.getValue());
}

double DriveSubsystem::getRightEncoder() {
  return EncoderUtil::getInches(driveTrain.getSensorVals()[1], BACK_WHEEL_DIAMETER.getValue());
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

void DriveSubsystem::turnAngleAsync(double angle) {
  driveTrain.turnAngleAsync(angle * okapi::degree);
}

void DriveSubsystem::turnDegreesAsync(double degrees) {
  driveTrain.turnAngleAsync(degrees);
}

void DriveSubsystem::generatePath(std::initializer_list<okapi::Point> pathPoints, std::string pathName) {
  profileController.generatePath(pathPoints, pathName);
}

void DriveSubsystem::followPath(std::string pathName, bool backwards, bool waitTilSettled) {
  profileController.setTarget(pathName, backwards);
  if(waitTilSettled) {
    profileController.waitUntilSettled();
  }
}

void DriveSubsystem::adjustPath(std::initializer_list<okapi::Point> pathPoints) {
  profileController.moveTo(pathPoints);
}

bool DriveSubsystem::isPathCompleted() {
  return profileController.isSettled();
}
