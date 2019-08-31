#include "User/LiftSubsystem.h"
#include <cmath>
#include "User/Constants.h"


LiftSubsystem::LiftSubsystem(okapi::Controller iDriverController) : driverController(iDriverController)
  , leftLiftMotor(LEFT_LIFT_MOTOR_PORT)
  , rightLiftMotor(-RIGHT_LIFT_MOTOR_PORT)
  , liftMotors({this->leftLiftMotor, this->rightLiftMotor})
  , liftController(okapi::AsyncControllerFactory::posIntegrated(liftMotors))
  , intakeMotor(INTAKE_MOTOR_PORT)
  , clampMotor(CLAMP_MOTOR_PORT)
  , beamBreak(LIGHT_SENSOR_PORT)
{
  targetHeight = HOME;
  manualStatus = false;

  liftMotors.setGearing(okapi::AbstractMotor::gearset::red);
  liftMotors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

  clampMotor.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  // Set current state to initialize state
  m_stateVal = LiftState::kInitialize;
}


void LiftSubsystem::initialize() {
  beamBreak.calibrate();
}



void LiftSubsystem::reset() {

}

void LiftSubsystem::disablePID() {
  liftController.flipDisable(true);
}

void LiftSubsystem::enablePID() {
  liftController.flipDisable(false);
}

bool LiftSubsystem::manualMode() {
  if(driverController.getDigital(okapi::ControllerDigital::Y)) {
    manualStatus = !manualStatus;
  }
  return manualStatus;
}

bool LiftSubsystem::home() {
  disablePID();
  // Move arm down
  liftController.controllerSet(-0.1);
  if(leftLiftMotor.getCurrentDraw() > 0) {
    liftController.tarePosition();
    liftController.stop();
    enablePID();
    return true;
  }
  return false;
}

void LiftSubsystem::stop() {
  liftController.setTarget(0);
  liftController.reset();
  liftController.stop();
}

void LiftSubsystem::update() {

  switch (m_stateVal) {
    case (LiftState::kInitialize):
      /*
       If current state is kInitialize,
       run the initialize function and set the next state to be teleop
       */
      nextState = LiftState::kTeleopDrive;

      break;
    case (LiftState::kTeleopDrive):

      // Left Bumper is outtake
      if (driverController.getDigital(okapi::ControllerDigital::L1)) {
        clampMotor.moveAbsolute(10, 20);
      } else {
        clampMotor.moveAbsolute(10, 20);
      }

      // Spin the intake wheels
      if(driverController.getDigital(okapi::ControllerDigital::R1)) {
        intakeMotor.controllerSet(0.4);
      } else {
        intakeMotor.controllerSet(0.0);
      }

      // If manual mode is selected
      if (manualMode()) {
        // Disable PID
        liftController.setTarget(0);
        disablePID();
        // If Up arrow is pressed move arm up slowly
        if (driverController.getDigital(okapi::ControllerDigital::up)) {
          liftController.controllerSet(0.2);
        // If down arrow is pressed move arm down slowly
        } else if (driverController.getDigital(okapi::ControllerDigital::down)) {
          liftController.controllerSet(-0.1);
        } else {
          liftController.controllerSet(0);
        }

      } else {
        // enablePID
        enablePID();
        // If up is pressed make the target height 6 inches taller
        if (driverController.getDigital(okapi::ControllerDigital::up)) {
          targetHeight += HEIGHT_OF_CUBE;
        // If down is pressed make the target height 6 inches shorter
        } else if (driverController.getDigital(okapi::ControllerDigital::down)) {
          targetHeight -= HEIGHT_OF_CUBE;
        // If A is pressed go to tower scoring position
      } else if (driverController.getDigital(okapi::ControllerDigital::A)) {
          targetHeight = HEIGHT_OF_CUBE + HEIGHT_OF_TOWER;
        // If Right bumper is pressed go to home to intake
        } else if (driverController.getDigital(okapi::ControllerDigital::R1)) {
          targetHeight = HOME;
        // If X is pressed, go to tower height to descore cube
        } else if (driverController.getDigital(okapi::ControllerDigital::X)) {
          targetHeight = HEIGHT_OF_TOWER;

        }

        // If target height is less than home, set target height to HOME
        if (targetHeight <= HOME)
          targetHeight = HOME;
        // If target height is greater than MAX_HEIGHT, set target height to MAX_HEIGHT
        if (targetHeight >= LIFT_TOP_HEIGHT)
          targetHeight = LIFT_TOP_HEIGHT;

        liftController.setTarget(targetHeight);


      break;
  }

  // Set current state to next state
  m_stateVal = nextState;
}
