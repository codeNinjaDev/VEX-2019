#include "User/LiftSubsystem.h"
#include <cmath>
#include "User/Constants.h"


LiftSubsystem::LiftSubsystem(okapi::Controller iDriverController) : driverController(iDriverController)
  , leftLiftMotor(-LEFT_LIFT_MOTOR_PORT)
  , rightLiftMotor(RIGHT_LIFT_MOTOR_PORT)
  , liftMotors({this->leftLiftMotor, this->rightLiftMotor})
  , intakeMotor(INTAKE_MOTOR_PORT)
  , clampMotor(CLAMP_MOTOR_PORT)
  , cubeSensor(LIGHT_SENSOR_PORT)
  , pidController((1/24), 0, 0, 0.7, 2, true)
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
  if(driverController.getDigital(okapi::ControllerDigital::Y)) {
    driverController.clearLine(1);
    manualStatus = !manualStatus;
  }
  return manualStatus;
}

//Converts inches to degrees
double LiftSubsystem::setHeight(double inches) {
  //Kinda sorta
return inches * 47.5;
}
double LiftSubsystem::getHeight() {
  //Kinda sorta
  return liftMotors.getPosition() / 47.5;
}
void LiftSubsystem::stop() {

  liftMotors.controllerSet(0);
}

void LiftSubsystem::update() {

    // Left Bumper is outtake
    if (driverController.getDigital(okapi::ControllerDigital::L1)) {
      clampMotor.moveAbsolute(100, 200);
    } else {
      clampMotor.moveAbsolute(0, 200);
    }

    // Spin the intake wheels
    if(driverController.getDigital(okapi::ControllerDigital::R1)) {
      intakeMotor.controllerSet(0.6);
    } else {
      intakeMotor.controllerSet(0.0);
    }

    // If manual mode is selected
    if (manualMode()) {
      // Disable PID
      driverController.setText(1, 1, "Manual Mode");
      // If Up arrow is pressed move arm up slowly
      if (driverController.getDigital(okapi::ControllerDigital::up)) {
        liftMotors.controllerSet(0.1);
      // If down arrow is pressed move arm down slowly
      } else if (driverController.getDigital(okapi::ControllerDigital::down)) {

        liftMotors.controllerSet(-0.1);
      } else {
        liftMotors.controllerSet(0);
      }


    } else {
      //AUTOMATIC
      // enablePID
      driverController.setText(1, 1, "AUTOMATIC");

      if (driverController.getDigital(okapi::ControllerDigital::up)) {
        targetHeight += HEIGHT_OF_CUBE;
      // If down is pressed make the target height 6 inches shorter
      } else if (driverController.getDigital(okapi::ControllerDigital::down)) {
        targetHeight -= HEIGHT_OF_CUBE;
      // If A is pressed go to tower scoring position
      } else if (driverController.getDigital(okapi::ControllerDigital::A)) {
        targetHeight = HEIGHT_OF_CUBE + HEIGHT_OF_TOWER;
      // If Right bumper is pressed go to home to intake
      } else if (driverController.getDigital(okapi::ControllerDigital::B)) {
          targetHeight = HOME;
        // If X is pressed, go to tower height to descore cube
      } else if (driverController.getDigital(okapi::ControllerDigital::X)) {
          targetHeight = HEIGHT_OF_TOWER;

      }

      // If target height is less than home, set target height to HOME
      if (targetHeight <= HOME) {
        targetHeight = HOME;
      }
      // If target height is greater than MAX_HEIGHT, set target height to MAX_HEIGHT
      if (targetHeight >= LIFT_TOP_HEIGHT) {
        targetHeight = LIFT_TOP_HEIGHT;
      }

      if (driverController.getDigital(okapi::ControllerDigital::right)) {
        if(cubeSensor.get_value() && (getHeight() > 2)) {
          targetHeight = 0;
        } else if (cubeSensor.get_value()) {
          targetHeight = HEIGHT_OF_CUBE;
        }
      }
      pidController.setSetpoint(targetHeight);
      liftMotors.controllerSet( pidController.run(getHeight()) );
      driverController.setText(2, 1, "Output: " + pidController.run(getHeight());
      driverController.setText(3, 1, "Target: " + targetHeight);

    }
  }
}
