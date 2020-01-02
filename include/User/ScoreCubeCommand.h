/*
 * RemoteControl.h
 *
 *  Created on: Jan 7, 2017
 *      Author: mikechacko
 */

#ifndef SCORECUBECOMMAND_H_
#define SCORECUBECOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "TraySubsystem.h"
/**
 * Base class for autonomous actions.
 * All funtions of this class must be implemented in child classes
 *
 */
class ScoreCubeCommand : public Command {
public:

	ScoreCubeCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TowerPosition position, double maxSpeed);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
	std::shared_ptr<TraySubsystem> tray;
	double maxSpeed, timeout;

	TraySubsystem::TowerPosition position;
};

#endif /* COMMAND_H_ */
