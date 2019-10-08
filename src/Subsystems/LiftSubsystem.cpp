#include "User/LiftSubsystem.h"
#include <cmath>
#include "User/Constants.h"


LiftSubsystem::LiftSubsystem(okapi::Controller iDriverController, okapi::Controller iOperatorController) : driverController(iDriverController), operatorController(iOperatorController)
  , leftLiftMotor(-LEFT_LIFT_MOTOR_PORT)
  , rightLiftMotor(RIGHT_LIFT_MOTOR_PORT)
  , liftMotors({this->leftLiftMotor, this->rightLiftMotor})
  , intakeMotor(INTAKE_MOTOR_PORT)
  , clampMotor(-CLAMP_MOTOR_PORT)
{
  targetHeight = HOME;
  manualStatus = false;

  liftMotors.setGearing(okapi::AbstractMotor::gearset::red);
  liftMotors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  liftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  clampMotor.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  // Set current state to initialize state
  m_stateVal = LiftState::kInitialize;

}


void LiftSubsystem::initialize() {
  reset();
}



void LiftSubsystem::reset() {
  liftMotors.tarePosition();
}

bool LiftSubsystem::manualMode() {
  if(operatorController.operator[](okapi::ControllerDigital::Y).changedToPressed()) {
    operatorController.rumble(".");
    manualStatus = !manualStatus;
  }
  return manualStatus;
}


void LiftSubsystem::stop() {

  liftMotors.moveVelocity(0);
}

void LiftSubsystem::update() {
  // Left Bumper is outtake
  if (operatorController.getDigital(okapi::ControllerDigital::R1)) {
    clampMotor.moveAbsolute(200, 100);
  } else {
    clampMotor.moveAbsolute(0, 200);
  }

  // Spin the intake wheels
  if(driverController.getDigital(okapi::ControllerDigital::R1)) {
    intakeMotor.controllerSet(1);
  } else {
    intakeMotor.controllerSet(0.0);
  }

  if(manualMode()) {
    if (operatorController.getDigital(okapi::ControllerDigital::L1)) {
      liftMotors.moveVelocity(75);
    // If down arrow is pressed move arm down slowly
  } else if (operatorController.getDigital(okapi::ControllerDigital::L2)) {

      liftMotors.moveVelocity(-50);
    } else {
      liftMotors.moveVelocity(0);
    }

  } else {
    //AUTOMATIC
    // enablePID
    //driverController.setText(1, 1, "AUTOMATIC");

    if (operatorController.operator[](okapi::ControllerDigital::L1).changedToPressed()) {
      targetHeight += HEIGHT_OF_CUBE;
    // If down is pressed make the target height 6 inches shorter
  } else if (operatorController.operator[](okapi::ControllerDigital::L2).changedToPressed()) {
        targetHeight -= HEIGHT_OF_CUBE;
      // If A is pressed go to tower scoring position
    } else if (operatorController.operator[](okapi::ControllerDigital::A).changedToPressed()) {
        targetHeight = HEIGHT_OF_CUBE + HEIGHT_OF_TOWER;
      // If Right bumper is pressed go to home to intake
    } else if (operatorController.operator[](okapi::ControllerDigital::B).changedToPressed()) {
        targetHeight = HOME;
      // If X is pressed, go to tower height to descore cube
    } else if (operatorController.operator[](okapi::ControllerDigital::X).changedToPressed()) {
        targetHeight = HEIGHT_OF_TOWER;

    } else if (operatorController.operator[](okapi::ControllerDigital::R2).changedToPressed()) {
        targetHeight = 200/48;
        operatorController.rumble("-");

    }

    // If target height is less than home, set target height to HOME
    if (targetHeight <= HOME) {
      targetHeight = HOME;
    }
    if(abs(liftMotors.getPosition()) > 1500) {
      LIFT_TOP_HEIGHT--;
    }
    // If target height is greater than MAX_HEIGHT, set target height to MAX_HEIGHT
    if (targetHeight >= LIFT_TOP_HEIGHT) {
      targetHeight = LIFT_TOP_HEIGHT;
    }


    liftMotors.moveAbsolute(targetHeight * 48, 100);

  }
}
