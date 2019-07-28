#include "main.h"

#include "user/Command.h"
#include "user/CommandRunner.h"
#include "user/CommandFactory.h"
#include "user/DriveSubsystem.h"
#include "user/LogVelocityCommand.h"
#include "user/LogPositionCommand.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  okapi::Controller master;
  std::unique_ptr<DriveSubsystem> drive (new DriveSubsystem(master));
  CommandRunner::runCommand(CommandFactory::create(new LogVelocityCommand(std::move(drive), 10)));
  CommandRunner::runCommand(CommandFactory::create(new LogPositionCommand(std::move(drive), 10)));

}
