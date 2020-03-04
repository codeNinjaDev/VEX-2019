#include "User/CommandRunner.h"


void CommandRunner::runCommand(Command* rawCommand, double timeout) {
  std::unique_ptr<Command> command(rawCommand);
  okapi::Timer timer = okapi::Timer();

  double startTime = timer.millis().getValue();
  double currentTime = startTime;
  command->start();
  // While the command is not finished and it is still autonomous, run the command
  while((!command->isFinished() && pros::competition::is_autonomous()) && ((currentTime - startTime) < (timeout * 1000))) {
    command->update();
    currentTime = timer.millis().getValue();
    pros::delay(20);
  }
  // End the command
  command->finish();
}


void CommandRunner::runCommand(std::unique_ptr<Command> command, double timeout) {
  okapi::Timer timer = okapi::Timer();

  double startTime = timer.millis().getValue();
  double currentTime = startTime;
  command->start();
  // While the command is not finished and it is still autonomous, run the command
  while((!command->isFinished() && pros::competition::is_autonomous()) && ((currentTime - startTime) < (timeout * 1000))) {
    command->update();
    currentTime = timer.millis().getValue();
    pros::delay(20);
  }
  // End the command
  command->finish();
}
void CommandRunner::runCommandGroup(std::vector<std::unique_ptr<Command>> commandGroup, double timeout) {
  // Iterates through array of commands
  for(int i = 0; i < commandGroup.size(); i++) {
      // Runs the queried command
      runCommand(std::move(commandGroup[i]), timeout);
    }
}
