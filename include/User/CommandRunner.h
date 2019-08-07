
#ifndef COMMANDRUNNER_H_
#define COMMANDRUNNER_H_
#include "user/command.h"

/**
 * Class that runs and "schedules" a command
 */
class CommandRunner {
public:
  /**
   * Runs the command's start function, then
   * loops the update function until the isFinished function returns true.
   * Finally, it runs the finish() function.
   * @param command The command to be run
   */
  static void runCommand(std::unique_ptr<Command> command);
  /**
   * Runs an array of commands sequentially
   * @param command An array(vector) of commands
   */
  static void runCommandGroup(std::vector<std::unique_ptr<Command>> commandGroup);

};

#endif
