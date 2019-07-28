
#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_
#include "user/command.h"
class CommandFactory {
public:
  static std::unique_ptr<Command> create(Command* command);

};

#endif
