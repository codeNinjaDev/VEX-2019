#include "user/commandfactory.h"

std::unique_ptr<Command> CommandFactory::create(Command* command) {
  std::unique_ptr<Command> commandPointer(command);
  return commandPointer;
};
