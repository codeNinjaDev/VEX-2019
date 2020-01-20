#ifndef DRIVETOPOINTCOMMAND_H_
#define DRIVETOPOINTCOMMAND_H_

#include "../main.h"
#include "Command.h"
#include "DriveSubsystem.h"
#include <iostream>
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <string>

class DriveToPointCommand : public Command {
public:

	DriveToPointCommand(std::shared_ptr<DriveSubsystem> drive, okapi::QLength forwardCoord, okapi::QLength sideCoord, okapi::QAngle finalHeading, bool reverse);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::shared_ptr<DriveSubsystem> drive;
  okapi::QLength forwardCoord, sideCoord;
  okapi::QAngle finalHeading;
	bool reverse;

};

#endif
