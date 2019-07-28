#include "user/commandrunner.h"


CommandRunner::~CommandRunner() {
}

void CommandRunner::runCommand(std::unique_ptr<Command> command) {

  command->start();

  while(!command->isFinished() && pros::competition::is_autonomous()) {
    command->update();
    pros::delay(20);
  }

  command->finish();
}

void CommandRunner::runCommandGroup(std::vector<std::unique_ptr<Command>> commandGroup) {
  for(int i = 0; i < commandGroup.size(); i++) {
      runCommand(std::move(commandGroup[i]));
    }
}
