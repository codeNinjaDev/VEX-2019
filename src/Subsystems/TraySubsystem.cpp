#include "User/TraySubsystem.h"
#include <cmath>
#include "User/Constants.h"


TraySubsystem::TraySubsystem(okapi::Controller iDriverController, okapi::Controller iOperatorController) : driverController(iDriverController)
  , operatorController(iOperatorController)
  , trayMotor(-TRAY_MOTOR_PORT)
  , intakeArmMotor(ARM_MOTOR_PORT)
  , leftIntakeMotor(LEFT_INTAKE_MOTOR_PORT)
  , rightIntakeMotor(-RIGHT_INTAKE_MOTOR_PORT)
  , intakeMotors({this->leftIntakeMotor, this->rightIntakeMotor})
  , limitSwitch(LIMIT_SWITCH_PORT)
  , intakeRollersButton(okapi::ControllerId::master ,okapi::ControllerDigital::R1)
  , outtakeMidTowerButton(okapi::ControllerId::master, okapi::ControllerDigital::L1)
  , outtakeHighTowerButton(okapi::ControllerId::master, okapi::ControllerDigital::up)
  , scoreStackButton(okapi::ControllerId::partner, okapi::ControllerDigital::R2)
  , slantButton(okapi::ControllerId::partner, okapi::ControllerDigital::L2)
  , moveLowTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::X)
  , moveMidTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::L1)
  , moveHighTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::R1)
{


  trayMotor.setGearing(okapi::AbstractMotor::gearset::green);
  trayMotor.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  //trayMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  intakeArmMotor.setGearing(okapi::AbstractMotor::gearset::red);
  intakeArmMotor.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

  intakeMotors.setGearing(okapi::AbstractMotor::gearset::green);
  intakeMotors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::rotations);


  // Set current state to initialize state
  m_stateVal = RobotState::kInitialize;

}


void TraySubsystem::initialize() {
  reset();
}



void TraySubsystem::reset() {
  trayMotor.tarePosition();
  intakeArmMotor.tarePosition();
}


void TraySubsystem::stop() {

  trayMotor.moveVelocity(0);
  intakeArmMotor.moveVelocity(0);
  intakeMotors.moveVelocity(0);
}

void TraySubsystem::update() {
  switch(m_stateVal) {
    case RobotState::kInitialize:

      nextState = RobotState::kTeleopDrive;
      break;

    case RobotState::kTeleopDrive:
        // Driver functions

      if(intakeRollersButton.isPressed()) {
        // If driver wants to intake cube, run intake at 100 rpm or half speed
        intakeMotors.moveVelocity(100);
      } else if(outtakeMidTowerButton.isPressed()) {
        // If driver wants to outtake cube or score in low towers, run intake at -100 rpm or half negative velocity
        intakeMotors.moveVelocity(-100);
      } else if(outtakeHighTowerButton.isPressed()) {
        // Shoot cube out as fast as possible
        intakeMotors.moveVelocity(-200);
      } else {
        intakeMotors.moveVelocity(0);
      }

      // Operator functions

      // Tray functions
      if (scoreStackButton.isPressed()) {
        trayMotor.moveAbsolute((double) TrayPosition::kStack, 100);
      } else {
        trayMotor.moveAbsolute((double) TrayPosition::kSlant, 100);
      }

      // Arm functions
      if(moveLowTowerButton.isPressed()) {
        intakeArmMotor.moveAbsolute((double) IntakePosition::kLowTower, 75);
      } else if(moveMidTowerButton.isPressed()) {
        intakeArmMotor.moveAbsolute((double) IntakePosition::kMidTower, 100);
      } else if(moveHighTowerButton.isPressed()) {
        intakeArmMotor.moveAbsolute((double) IntakePosition::kHighTower, 100);
      } else {
        intakeArmMotor.moveAbsolute((double) IntakePosition::kIntake, 80);
      }

      break;
  }
  m_stateVal = nextState;
}
