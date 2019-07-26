
#ifndef COMMANDRUNNER_H_
#define COMMANDRUNNER_H_
#include "user/command.h"
class CommandRunner {
public:
  CommandRunner(Command command);

  void runCommand();
private:
  Command command;
};

#endif
