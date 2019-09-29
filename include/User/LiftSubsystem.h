#ifndef LIFTSUBSYSTEM_H_
#define LIFTSUBSYSTEM_H_
#include "../main.h"
#include "Subsystem.h"
#include <iostream>

/**
 * Gearset 100:1
 * Gear ratio 7:1
 * Class that controls the lift
 * @param driverController VEX Gamepad
 */
class LiftSubsystem : public Subsystem {
public:

	LiftSubsystem(okapi::Controller driverController, okapi::Controller operatorController);

	void stop();
	void update();
	void reset();
  void initialize();

	/**
	 * State of the Lift
	 */
	enum LiftState {
		kInitialize, kTeleopDrive
	};

	okapi::Motor leftLiftMotor, rightLiftMotor;
	okapi::MotorGroup liftMotors;

private:
	// Current state of drive train
	uint32_t m_stateVal;
	// Upcoming state of drive train
  uint32_t nextState;

  okapi::Controller driverController, operatorController;
	okapi::Motor intakeMotor;
	okapi::Motor clampMotor;

	double targetHeight = 0;
	bool manualMode();
	bool manualStatus;



};

#endif
