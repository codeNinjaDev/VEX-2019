
#ifndef COMMANDRUNNER_H_
#define COMMANDRUNNER_H_
#include "user/command.h"
class CommandRunner {
public:
  CommandRunner();
  ~CommandRunner();
  static void runCommand(Command* command);
  static void runCommandGroup(std::vector<Command*> commandGroup);
private:

};

#endif
