/*
 * RemoteControl.h
 *
 *  Created on: Jan 7, 2017
 *      Author: mikechacko
 */

#ifndef COMMAND_H_
#define COMMAND_H_
#include "../main.h"
/**
 * Base class for autonomous actions.
 * All funtions of this class must be implemented in child classes
 *
 */
class Command {
public:

	/**
	 * Abstract function that is called before the while loop only once. Common use case is to setup the command.
	 */
	virtual void start() = 0;
	/**
	 * Abstract function that is run in a while loop until *isFinished()* returns true and contains the meat of the command, such as running motors.
	 */
  virtual void update() = 0;
	/**
	 * Abstract function that runs in a while loop and continously checks if the command should end. If true, ends while loop.
	 * Common use case is to check if timeout for command is exceeded
	 * @return True if command should end, false if it should not.
	 */
  virtual bool isFinished() = 0;
	/**
	 * Abstract function that runs after the while loop and only once.
	 * Normally wraps up a command and gets the robot ready to transition to a new command.
	 */
	virtual void finish() = 0;

	// These variables are to ensure that there is a time limit allotted for each command and that no command
	// exceeds the limit (also called a timeout)

	/**
	 * Variable to store the starting timestamp of the command.
	 */
	double startTime;
	/**
	 * Variable to store the maximum allowed time for a command to run.
	 */
	double goalTime;
	okapi::Timer timer;

};

#endif /* COMMAND_H_ */
