#include "user/commandrunner.h"


CommandRunner::~CommandRunner() {
}

void CommandRunner::runCommand(Command* command) {

  command->start();

  while(!command->isFinished() && pros::competition::is_autonomous()) {
    command->update();
    pros::delay(20);
  }

  command->finish();
  delete command;
}

void CommandRunner::runCommandGroup(std::vector<Command*> commandGroup) {
  for(int i = 0; i < commandGroup.size(); i++) {
      runCommand(commandGroup[i]);
    }
}
