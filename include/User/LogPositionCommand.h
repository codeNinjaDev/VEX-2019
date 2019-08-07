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

/**
 * Command to log the distance of the robot (to a csv file) while spinning
 * in order to find the max constants for motion profiling.
 */
class LogPositionCommand : public Command {
public:
	/**
	 *
	 * @param drive   Needs drive subsystem
	 * @param timeout Time limit for the command
	 */
	LogPositionCommand(std::shared_ptr<DriveSubsystem> drive, double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::shared_ptr<DriveSubsystem> driveTrain;
	// File to log the position vs time data to.
  FILE* logFile;
  double currentPosition;

};

#endif
