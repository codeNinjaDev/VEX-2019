#ifndef HOMELIFTCOMMAND_H_
#define HOMELIFTCOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "LiftSubsystem.h"
#include <iostream>

#include <iostream>
#include <fstream>
#include <string>
class HomeLiftCommand : public Command {
public:

	HomeLiftCommand(std::shared_ptr<LiftSubsystem> lift, double timeout);

	void start();
	void update();
	bool isFinished();
  void finish();

private:
  std::shared_ptr<LiftSubsystem> lift;
  

};

#endif
