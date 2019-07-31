#include "User/CommandGroup.h"

void CommandGroup::addSequentialCommand(std::unique_ptr<Command> command) {
  this->addedCommands.push_back(command);
}

void CommandGroup::run() {
  CommandRunner::runCommandGroup(addedCommands);
}
