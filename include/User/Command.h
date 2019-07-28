/*
 * RemoteControl.h
 *
 *  Created on: Jan 7, 2017
 *      Author: mikechacko
 */

#ifndef COMMAND_H_
#define COMMAND_H_
#include "../main.h"
class Command {
public:


	virtual void start() = 0;
  virtual void update() = 0;
  virtual bool isFinished() = 0;
	virtual void finish() = 0;

	double startTime;
	double goalTime;
	okapi::Timer timer;

};

#endif /* COMMAND_H_ */
