/*
 * RemoteControl.h
 *
 *  Created on: Jan 7, 2017
 *      Author: mikechacko
 */

#ifndef MOVETRAYCOMMAND_H_
#define MOVETRAYCOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "TraySubsystem.h"
/**
 * Base class for autonomous actions.
 * All funtions of this class must be implemented in child classes
 *
 */
class MoveTrayCommand : public Command {
public:

	MoveTrayCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TrayPosition position, double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
	std::shared_ptr<TraySubsystem> tray;

	TraySubsystem::TrayPosition position;
};

#endif /* COMMAND_H_ */
