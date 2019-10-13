#ifndef DRIVESUBYSTEM_H_
#define DRIVESUBYSTEM_H_
#include "../main.h"
#include "Subsystem.h"
#include "User/EncoderUtil.h"

#include <iostream>

/**
 * Class that controls the drivetrain
 * @param driverController VEX Gamepad
 */
class DriveSubsystem : public Subsystem {
public:

	DriveSubsystem(okapi::Controller driverController);

	void stop();
	void update();
	void reset();
  void initialize();
	/**
	 * Get the distance of the left encoder in inches
	 * @return Distance of left side in inches
	 */
	double getLeftEncoder();
	/**
	 * Get the distance of the right encoder in inches
	 * @return Distance of right side in inches
	 */
	double getRightEncoder();

	/**
	 * Drive the robot using arcade drive
	 * @param forward Power (-1 to 1) to go forward
	 * @param rotate  Power (-1 to 1) to rotate
	 * @param teleOp  Square the input variables for easy control
	 */
	void arcadeDrive(double forward, double rotate, bool teleOp);
	/**
	 * Drive the robot using arcade drive
	 * @param myLeft Power (-1 to 1) for left side
	 * @param myRight  Power (-1 to 1) for right side
	 * @param teleOp  Square the input variables for easy control
	 */
	void tankDrive(double myLeft, double myRight, bool teleOp);

	void moveMetersAsync(double meters);
	void moveInchesAsync(double inches);
	void turnDegrees(double angle);

	void generatePath(std::initializer_list<okapi::Point> pathPoints, std::string pathName);
	void followPath(std::string pathName, bool backwards, bool waitTilSettled);
	void adjustPath(std::initializer_list<okapi::Point> pathPoints);
	bool isPathCompleted();
	okapi::Motor backLeftDriveMotor, backRightDriveMotor, frontLeftDriveMotor, frontRightDriveMotor;
	okapi::MotorGroup leftMotors, rightMotors;

	okapi::ChassisControllerIntegrated driveTrain;
	/**
	 * State of the Subsystem
	 */
	enum DriveState {
		kInitialize, kTeleopDrive
	};





private:
	// Current state of drive train
	uint32_t m_stateVal;
	// Upcoming state of drive train
  uint32_t nextState;
  okapi::Controller driverController;

	okapi::ControllerButton SlowDown1, SlowDown2;
	okapi::ControllerButton toggleDriveButton, toggleDefenseButton;
	okapi::AsyncMotionProfileController profileController;
	/**
	 * Squqre the variable without changing the sign
	 * @param input The value to be squared
	 */
	double squareInput(double input);
	bool toggleDrive;
	bool toggleDefense;

};

#endif
