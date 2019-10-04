#include "User/CommandFactory.h"

std::unique_ptr<Command> CommandFactory::create(Command* command) {
  // Create unique_ptr
  std::unique_ptr<Command> commandPointer(command);
  // Return unique_ptr
  return commandPointer;
};
