#ifndef DRIVEANDINTAKECOMMAND_H_
#define DRIVEANDINTAKECOMMAND_H_

#include "../main.h"
#include "Command.h"
#include "DriveSubsystem.h"
#include "TraySubsystem.h"
#include <iostream>

#include <iostream>
#include <fstream>
#include <string>

class DriveAndIntakeCommand : public Command {
public:

	DriveAndIntakeCommand(std::shared_ptr<DriveSubsystem> drive, std::shared_ptr<TraySubsystem> tray,double distance, double maxSpeed,  double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::shared_ptr<DriveSubsystem> drive;
	std::shared_ptr<TraySubsystem> tray;

  double distance, maxSpeed;


};

#endif
