#include "User/TraySubsystem.h"
#include <cmath>
#include "User/Constants.h"


TraySubsystem::TraySubsystem(okapi::Controller iDriverController, okapi::Controller iOperatorController) : driverController(iDriverController)
  , operatorController(iOperatorController)
  , trayMotor(TRAY_MOTOR_PORT)
  , cubeScorer(ARM_MOTOR_PORT)
  , leftIntakeMotor(LEFT_INTAKE_MOTOR_PORT)
  , rightIntakeMotor(-RIGHT_INTAKE_MOTOR_PORT)
  , intakeMotors({this->leftIntakeMotor, this->rightIntakeMotor})
  , limitSwitch(LIMIT_SWITCH_PORT)
  , intakeRollersButton(okapi::ControllerId::master ,okapi::ControllerDigital::R1)
  , outtakeRollersButton(okapi::ControllerId::master ,okapi::ControllerDigital::L1)
  , scoreStackButton(okapi::ControllerId::partner, okapi::ControllerDigital::R2)
  , slantButton(okapi::ControllerId::partner, okapi::ControllerDigital::L2)
  , lowTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::L1)
  , highTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::down)
  , extendTrayButton(okapi::ControllerId::partner, okapi::ControllerDigital::up)
{


  trayMotor.setGearing(okapi::AbstractMotor::gearset::red);
  trayMotor.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  //trayMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  cubeScorer.setGearing(okapi::AbstractMotor::gearset::red);
  cubeScorer.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  cubeScorer.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
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
  cubeScorer.tarePosition();
}


void TraySubsystem::stop() {

  trayMotor.moveVelocity(0);
  cubeScorer.moveVelocity(0);
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
        intakeCube();
      } else if(outtakeRollersButton.isPressed()){
        outtakeCube(100);
      } else {
        intakeMotors.moveVelocity(0);
      }

      // Operator functions

      // Tray functions
      if (scoreStackButton.isPressed()) {
        moveTray(TrayPosition::kStack, 100);
      } else {
        moveTray(TrayPosition::kSlant, 100);
      }

      // Arm functions
      if(lowTowerButton.isPressed()) {
        scoreTower(TowerPosition::kLowTower,75);
      } else if(highTowerButton.isPressed()) {
        scoreTower(TowerPosition::kHighTower,75);
      } else if(extendTrayButton.isPressed()) {
        scoreTower(TowerPosition::kExtendTray,75);
      } else {
        scoreTower(TowerPosition::kTray,80);
      }

      break;
  }
  m_stateVal = nextState;
}

void TraySubsystem::moveTray(TrayPosition position, double targetVelocity) {
  trayMotor.moveAbsolute((double) position, targetVelocity);
}

void TraySubsystem::scoreTower(TowerPosition position, double targetVelocity) {
  cubeScorer.moveAbsolute((double) position, targetVelocity);
}

void TraySubsystem::intakeCube() {
  intakeMotors.moveVelocity(200);
}

void TraySubsystem::outtakeCube(double targetSpeed) {
  intakeMotors.moveVelocity(-targetSpeed);
}
