#include "user/commandrunner.h"

CommandRunner::CommandRunner(Command command) : command(command);

void CommandRunner::runCommand() {
  command.start();

  while(!command.isFinished && pros::competition::is_autonomous()) {
    command.update();
  }

  command.finish();
  
}
