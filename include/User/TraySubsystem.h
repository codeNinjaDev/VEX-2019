#ifndef TRAYSUBSYSTEM_H_
#define TRAYSUBSYSTEM_H_
#include "../main.h"
#include "Subsystem.h"
#include <iostream>

/**

 * @param driverController VEX Gamepad for driver
 * @param operatorController VEX Gamepad for Operator
 */
class TraySubsystem : public Subsystem {
public:

	TraySubsystem(okapi::Controller driverController, okapi::Controller operatorController);

	void stop();
	void update();
	void reset();
  void initialize();

	/**
	 * State of the Robot
	 */
	enum RobotState {
		kInitialize, kTeleopDrive
	};

	/**
	 * Positions of the Intake Arm
	 */
	enum IntakePosition {
		kIntake = 0, kLowTower = 0, kMidTower = 0, kHighTower = 0
	};

	/**
	 * Positions of the Intake Arm
	 */
	enum TrayPosition {
		kSlant = 0, kStack = 457
	};

	void moveTray(TrayPosition position, double targetVelocity);
	void moveArm(IntakePosition position, double targetVelocity);
	void intakeCube();
	void outtakeCube(double targetVelocity);
	okapi::Motor trayMotor;

private:
	// Current state of robot
	uint32_t m_stateVal;
	// Upcoming state of robot
  uint32_t nextState;

  okapi::Controller driverController, operatorController;
	okapi::Motor intakeArmMotor;

	okapi::Motor leftIntakeMotor, rightIntakeMotor;
	okapi::MotorGroup intakeMotors;

	okapi::ADIButton limitSwitch;

	// Driver Buttons
	okapi::ControllerButton intakeRollersButton, outtakeMidTowerButton, outtakeHighTowerButton;

	// Operator Buttons
	okapi::ControllerButton scoreStackButton, slantButton, moveLowTowerButton, moveMidTowerButton, moveHighTowerButton;


};

#endif
