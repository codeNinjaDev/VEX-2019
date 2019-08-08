/*
 * RemoteControl.h
 *
 *  Created on: Jan 7, 2017
 *      Author: mikechacko
 */

#ifndef SRC_SUBSYSTEMS_SUBSYSTEM_H_
#define SRC_SUBSYSTEMS_SUBSYSTEM_H_

#include "user/constants.h"
#include "../main.h"

/**
 * Base class for subsystems of robot
 */
class Subsystem {
public:

	/**
	 * Abstract function that configures sensors and motors or anything else that needs
	 * to be done before the robot runs.
	 */
	virtual void initialize() = 0;
	/**
	 * Looped function to run subsystem motors
	 */
  virtual void update() = 0;
	/**
	 * Function to reset subsystems sensors, etc...
	 */
  virtual void reset() = 0;
	/**
	 * Function to stop subsystem operations such as setting motors to zero
	 */
	virtual void stop() = 0;
};

#endif /* SRC_SUBSYSTEMS_SUBSYSTEM */
