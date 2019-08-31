#include "user/commandrunner.h"


void CommandRunner::runCommand(Command* rawCommand) {
  std::unique_ptr<Command> command(rawCommand);
  command->start();
  // While the command is not finished and it is still autonomous, run the command
  while(!command->isFinished() && pros::competition::is_autonomous()) {
    command->update();
    pros::delay(20);
  }
  // End the command
  command->finish();
}

void CommandRunner::runCommand(std::unique_ptr<Command> command) {
  command->start();
  // While the command is not finished and it is still autonomous, run the command
  while(!command->isFinished() && pros::competition::is_autonomous()) {
    command->update();
    pros::delay(20);
  }
  // End the command
  command->finish();
}
void CommandRunner::runCommandGroup(std::vector<std::unique_ptr<Command>> commandGroup) {
  // Iterates through array of commands
  for(int i = 0; i < commandGroup.size(); i++) {
      // Runs the queried command
      runCommand(std::move(commandGroup[i]));
    }
}
