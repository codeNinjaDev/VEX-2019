
#ifndef COMMANDRUNNER_H_
#define COMMANDRUNNER_H_
#include "user/command.h"
class CommandRunner {
public:
  CommandRunner();
  ~CommandRunner();
  static void runCommand(std::unique_ptr<Command> command);
  static void runCommandGroup(std::vector<std::unique_ptr<Command>> commandGroup);
private:

};

#endif
