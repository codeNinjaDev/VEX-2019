#ifndef DRIVESUBYSTEM_H_
#define DRIVESUBYSTEM_H_
#include "../main.h"
#include "Subsystem.h"
#include "InchEncoder.h"

#include <iostream>


class DriveSubsystem : public Subsystem {
public:
	DriveSubsystem(okapi::Controller driverController);

	void stop();
	void update();
	void reset();
  void initialize();
	double getLeftEncoder();
	double getRightEncoder();


	void ArcadeDrive(double forward, double rotate, bool teleOp);
	void TankDrive(double myLeft, double myRight, bool teleOp);
	okapi::ChassisControllerIntegrated driveTrain;

	enum DriveState {
		kInitialize, kTeleopDrive
	};




private:
	uint32_t m_stateVal;
  uint32_t nextState;
  okapi::Controller driverController;
	InchEncoder leftEncoder, rightEncoder;

};

#endif
