
#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_
#include "User/Command.h"
/**
 * CLass to create a unique_ptr of a command
 */
class CommandFactory {
public:
  /**
   *
   * Static function to convert a raw Command pointer
   * into a safe, unique_ptr
   * @param  command Raw command pointer created with "new"
   * @return  safe unique command ptr
   */
  static std::unique_ptr<Command> create(Command* command);

};

#endif
