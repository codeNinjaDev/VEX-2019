#ifndef DRIVEDISTANCECOMMAND_H_
#define DRIVEDISTANCECOMMAND_H_

#include "../main.h"
#include "Command.h"
#include "DriveSubsystem.h"
#include <iostream>
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <string>

class DriveDistanceCommand : public Command {
public:

	DriveDistanceCommand(std::shared_ptr<DriveSubsystem> drive, double distance, double maxSpeed, double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::shared_ptr<DriveSubsystem> drive;
  double distance, maxSpeed;


};

#endif
