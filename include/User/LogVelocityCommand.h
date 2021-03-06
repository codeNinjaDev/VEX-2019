#ifndef LOGVELOCITYCOMMAND_H_
#define LOGVELOCITYCOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "DriveSubsystem.h"
#include <iostream>

#include <iostream>
#include <fstream>
#include <string>


class LogVelocityCommand : public Command {
public:
	LogVelocityCommand(std::shared_ptr<DriveSubsystem> drive, double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::shared_ptr<DriveSubsystem> driveTrain;
  FILE* logFile;
  double pastPosition, currentPosition, pastTime;

};

#endif
