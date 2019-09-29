#ifndef LIFTSUBSYSTEM_H_
#define LIFTSUBSYSTEM_H_
#include "../main.h"
#include "Subsystem.h"
#include "user/linearencoder.h"
#include <iostream>

/**
 * Gearset 100:1
 * Gear ratio 7:1
 * Class that controls the lift
 * @param driverController VEX Gamepad
 */
class LiftSubsystem : public Subsystem {
public:

	LiftSubsystem(okapi::Controller driverController);

	void stop();
	void update();
	void reset();
  void initialize();
	/**
	 * Get the height of the lift (inches)
	 */
	double getLiftEncoder();

  /**
   * Increase the height one cube height.
   */
  void stepLiftUp();

  /**
   * Decrease the height one cube height.
   */
  void stepLiftDown();

  /**
   * Go to the intake position and run intake wheels if on automatic, if on manual only control
   * wheels
   */
  void intakeCube();

  /**
   * Outtake cube with clamp; dedicated
   */
  void outtakeCube();

  /**
   * Descore tower cube
   */
  void descoreCubePosition();

  /**
   * Tower postion
   */
  void towerScorePostiton();
	/**
   * Disable PID
   */
	void disablePID();

	/**
	 * Enable pid
	 */
	void enablePID();

	/**
	 * Tare the encoder position when it hits the bottom
	 */
	bool home();
	/**
	 * State of the Lift
	 */
	enum LiftState {
		kInitialize, kTeleopDrive
	};
	double setHeight(double inches);
	double getHeight();
	okapi::Motor leftLiftMotor, rightLiftMotor;
	okapi::MotorGroup liftMotors;

private:
	// Current state of drive train
	uint32_t m_stateVal;
	// Upcoming state of drive train
  uint32_t nextState;

  okapi::Controller driverController;
	okapi::Motor intakeMotor;
	okapi::Motor clampMotor;

	double targetHeight = 0;
	bool manualMode();
	bool manualStatus;
	pros::ADIButton cubeSensor;

	PIDController pidController;


};

#endif
