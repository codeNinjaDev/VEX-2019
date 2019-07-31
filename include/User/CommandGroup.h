
#ifndef COMMANDGROUP_H_
#define COMMANDGROUP_H_
#include "user/command.h"
#include "user/commandrunner.h"

class CommandGroup {
public:

  void addSequentialCommand(std::unique_ptr<Command> command);
  // void addParallelCommand(std::unique_ptr<Command> command);
  void run();
private:
  std::vector<std::unique_ptr<Command>> addedCommands;
};

#endif
