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
class Subsystem {
public:


	virtual void initialize() = 0;
  virtual void update() = 0;
  virtual void reset() = 0;
	virtual void stop() = 0;
	static std::unique_ptr<Subsystem> toPointer(Subsystem* subsystem);
};

#endif /* SRC_SUBSYSTEMS_SUBSYSTEM */
