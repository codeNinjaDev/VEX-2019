#include "User/TraySubsystem.h"
#include <cmath>
#include "User/Constants.h"


TraySubsystem::TraySubsystem(okapi::Controller iDriverController, okapi::Controller iOperatorController) : driverController(iDriverController)
  , operatorController(iOperatorController)
  , trayMotor(TRAY_MOTOR_PORT)
  , cubeScorer(-ARM_MOTOR_PORT)
  , leftIntakeMotor(LEFT_INTAKE_MOTOR_PORT)
  , rightIntakeMotor(-RIGHT_INTAKE_MOTOR_PORT)
  , intakeMotors({this->leftIntakeMotor, this->rightIntakeMotor})
  , limitSwitch(LIMIT_SWITCH_PORT)
  , intakeRollersButton(okapi::ControllerId::master ,okapi::ControllerDigital::R1)
  , outtakeRollersButton(okapi::ControllerId::master ,okapi::ControllerDigital::L1)
  , scoreStackButton(okapi::ControllerId::master, okapi::ControllerDigital::L2)
  , lowTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::L2)
  , midTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::L1)
  , intakePosButton(okapi::ControllerId::partner, okapi::ControllerDigital::B)
  , toggleManualTowerButton(okapi::ControllerId::partner, okapi::ControllerDigital::X)
  , manualUpButton(okapi::ControllerId::partner, okapi::ControllerDigital::up)
  , manualDownButton(okapi::ControllerId::partner, okapi::ControllerDigital::down)
{


  trayMotor.setGearing(okapi::AbstractMotor::gearset::red);
  trayMotor.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  trayMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  //trayMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  cubeScorer.setGearing(okapi::AbstractMotor::gearset::red);
  cubeScorer.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  cubeScorer.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  intakeMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  intakeMotors.setGearing(okapi::AbstractMotor::gearset::green);
  intakeMotors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::rotations);

  towerToggles = 0;
  toggleManualTower = false;
  // Set current state to initialize state
  m_stateVal = RobotState::kInitialize;

}

void TraySubsystem::moveTray(TrayPosition position, double targetVelocity) {
  double currPosition = trayMotor.getPosition();
  trayMotor.moveAbsolute((double) position, abs(targetVelocity - (90/(double) position)*currPosition));

}

void TraySubsystem::scoreTower(TowerPosition position, double targetVelocity) {
  cubeScorer.moveAbsolute((double) position, targetVelocity);
}

void TraySubsystem::intakeCube(){
  intakeMotors.moveVelocity(200);
}

void TraySubsystem::outtakeCube(double targetSpeed) {
  intakeMotors.moveVelocity(-targetSpeed);
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
      if (scoreStackButton.changedToPressed()) {
        stackTrayToggle = !stackTrayToggle;
      }

      if (toggleManualTowerButton.changedToPressed()) {
        toggleManualTower = !toggleManualTower;
        operatorController.rumble(".-.");
      }

      if(stackTrayToggle) {
        moveTray(TrayPosition::kStack, 100);
      } else {
        moveTray(TrayPosition::kSlant, 100);
      }

      if(midTowerButton.changedToPressed()) {
        towerToggles = 2;
      } else if(lowTowerButton.changedToPressed()) {
        towerToggles = 1;
      } else if(intakePosButton.changedToPressed()) {
        towerToggles = 0;
      }

      if(toggleManualTower) {
        if(manualUpButton.isPressed()) {
          cubeScorer.moveVelocity(50);
        } else if(manualDownButton.isPressed()) {
          cubeScorer.moveVelocity(-50);
        } else {
          cubeScorer.moveVelocity(0);
        }
      } else {
        if(towerToggles == 0) {
          scoreTower(TowerPosition::kIntake, 100);
        } else if(towerToggles == 1) {
          scoreTower(TowerPosition::kLowTower, 100);
        } else if(towerToggles == 2) {
          scoreTower(TowerPosition::kMidTower, 100);
        }

      }
      break;
  }
  m_stateVal = nextState;
}
