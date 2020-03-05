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
  , gyro(IMU_PORT)
  , leftMotors({backLeftDriveMotor, frontLeftDriveMotor})
  , rightMotors({backRightDriveMotor, frontRightDriveMotor})
  , driveTrain(okapi::ChassisControllerBuilder().withMotors(leftMotors, rightMotors).withDimensions(okapi::AbstractMotor::gearset::green, {{4.125_in, 10_in}, okapi::imev5GreenTPR}).build())
     // build an odometry chassis) // build an odometry chassis
    , SlowDown1(okapi::ControllerId::master, okapi::ControllerDigital::R2)
    , toggleDriveButton(okapi::ControllerId::master, okapi::ControllerDigital::right)
    , toggleDefenseButton(okapi::ControllerId::master, okapi::ControllerDigital::X)
{
  // Set current state to initialize state
  toggleDrive = false;
  toggleDefense = false;


  //driveTrain->getModel()->setEncoderUnits(okapi::AbstractMotor::encoderUnits::rotations);

  m_stateVal = DriveState::kInitialize;
}


void DriveSubsystem::initialize() {
  reset();
}

double normalizeAngle(double angle) {
    double newAngle = angle;
    while (newAngle <= -180) newAngle += 360;
    while (newAngle > 180) newAngle -= 360;
    return newAngle;
}

void DriveSubsystem::resetGyro() {
  gyro.reset();
}

double DriveSubsystem::getHeading() {
  return normalizeAngle(gyro.get_heading());
}


void DriveSubsystem::reset() {
  // Reset sensors and stop all drive motors
  leftMotors.tarePosition();
  rightMotors.tarePosition();
  driveTrain->getModel()->resetSensors();
}

void DriveSubsystem::stop() {
  driveTrain->stop();
  driveTrain->setMaxVelocity(200);

}

void DriveSubsystem::update() {

  switch (m_stateVal) {
    case (DriveState::kInitialize):
      /*
       If current state is kInitialize,
       run the initialize function and set the next state to be teleop
       */
      initialize();

      setBrakeMode(okapi::AbstractMotor::brakeMode::coast);


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


      if (toggleDrive) {
        arcadeDrive(driverController.getAnalog(okapi::ControllerAnalog::leftY)
          , driverController.getAnalog(okapi::ControllerAnalog::rightX)
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
    if (SlowDown1.isPressed()) {
      multiplier = 0.65;
      setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    } else {
      multiplier = 1;
      setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

    }
    okapi::AbstractMotor::brakeMode currBrake = leftMotors.getBrakeMode();

    if(toggleDefense) {
      setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    } else {
      setBrakeMode(currBrake);
    }
    if (teleOp) {
    // Square the joystick inputs, but keep the orignal sign
      driveTrain->getModel()->arcade(squareInput(forward) * multiplier, squareInput(rotate) * multiplier);
    } else {
      driveTrain->getModel()->arcade(forward * multiplier, rotate * multiplier);
    }

}

void DriveSubsystem::tankDrive(double myLeft, double myRight, bool teleOp) {

  double multiplier = 1;
  if (SlowDown1.isPressed()) {
    multiplier = 0.65;
    setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  } else {
    multiplier = 1;
    setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  }
  okapi::AbstractMotor::brakeMode currBrake = leftMotors.getBrakeMode();

  if(toggleDefense) {
    setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  } else {
    setBrakeMode(currBrake);
  }
  if (teleOp) {
    driveTrain->getModel()->tank((squareInput(myLeft) * multiplier), (squareInput(myRight) * multiplier));
  } else {
    driveTrain->getModel()->tank(myLeft * multiplier, myRight * multiplier);


  }

}

double DriveSubsystem::getLeftEncoder() {
  return EncoderUtil::getInches(driveTrain->getModel()->getSensorVals()[0], BACK_WHEEL_DIAMETER.getValue());
}

double DriveSubsystem::getRightEncoder() {
  return EncoderUtil::getInches(driveTrain->getModel()->getSensorVals()[1], BACK_WHEEL_DIAMETER.getValue());
}

double DriveSubsystem::squareInput(double input) {
  // Keeps the original sign, but squares the magnitude.
  return copysign(pow(input, 2), input);
}

void DriveSubsystem::moveMetersAsync(double meters) {
  reset();
  driveTrain->moveDistanceAsync(meters * okapi::meter);
}

void DriveSubsystem::moveInchesAsync(double inches) {
  reset();
  driveTrain->moveDistanceAsync(inches * okapi::inch);
}

void DriveSubsystem::turnAngleAsync(double angle) {
  reset();
  driveTrain->turnAngleAsync(angle * okapi::degree);
}

void DriveSubsystem::setBrakeMode(okapi::AbstractMotor::brakeMode brake) {
  frontLeftDriveMotor.setBrakeMode(brake);
  frontRightDriveMotor.setBrakeMode(brake);
  backLeftDriveMotor.setBrakeMode(brake);
  backRightDriveMotor.setBrakeMode(brake);
}
