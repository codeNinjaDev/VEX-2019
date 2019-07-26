#include "user/commandrunner.h"

CommandRunner::CommandRunner(Command* command) {
  this->command = command;
}

CommandRunner::~CommandRunner() {
  delete this->command;
}

void CommandRunner::runCommand() {
  command->start();

  while(!command->isFinished() && pros::competition::is_autonomous()) {
    command->update();
  }

  command->finish();

}
