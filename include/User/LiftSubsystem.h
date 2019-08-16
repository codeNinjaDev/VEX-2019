#ifndef LIFTSUBSYSTEM_H_
#define LIFTSUBSYSTEM_H_
#include "../main.h"
#include "Subsystem.h"
#include "user/linearencoder.h"
#include <iostream>

/**
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
	 * State of the Subsystem
	 */
	enum LiftState {
		kInitialize, kTeleopDrive
	};
private:
	// Current state of drive train
	uint32_t m_stateVal;
	// Upcoming state of drive train
  uint32_t nextState;
  okapi::Controller driverController;
	LinearEncoder liftEncoder;
  okapi::AsyncPosPIDController liftPID;

};

#endif
