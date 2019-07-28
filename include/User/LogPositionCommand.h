#ifndef LOGPOSITIONCOMMAND_H_
#define LOGPOSITIONCOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "InchEncoder.h"
#include "DriveSubsystem.h"
#include <iostream>

#include <iostream>
#include <fstream>
#include <string>


class LogPositionCommand : public Command {
public:
	LogPositionCommand(std::unique_ptr<DriveSubsystem> drive, double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::unique_ptr<DriveSubsystem> driveTrain;
  FILE* logFile;
  double currentPosition;

};

#endif
