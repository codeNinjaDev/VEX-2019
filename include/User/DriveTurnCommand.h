/*
 * RemoteControl.h
 *
 *  Created on: Jan 7, 2017
 *      Author: mikechacko
 */

#ifndef DRIVETURNCOMMAND_H_
#define DRIVETURNCOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "DriveSubsystem.h"


class DriveTurnCommand : public Command {
public:

	DriveTurnCommand(std::shared_ptr<DriveSubsystem> drive, double angle, double kP, bool absolute,double maxSpeed);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
	std::shared_ptr<DriveSubsystem> drive;
	double maxSpeed, angle, kP, offset;
};

#endif /* COMMAND_H_ */
