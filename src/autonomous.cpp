#include "main.h"

#include "user/Command.h"
#include "user/CommandRunner.h"
#include "user/CommandFactory.h"
#include "user/DriveSubsystem.h"
#include "user/LogVelocityCommand.h"
#include "user/LogPositionCommand.h"
#include "User/Constants.h"
#include "User/Extern.h"

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
void doNothingAuto();
/**
 * Spins the robot while logging the position vs time
 * @param std::shared_ptr<DriveSubsystem> Needed to drive
 */
void logPositionAuto(std::shared_ptr<DriveSubsystem>);
void logVelocityAuto(std::shared_ptr<DriveSubsystem>);

void autonomous() {
  okapi::Controller master;

  std::shared_ptr<DriveSubsystem> drive (new DriveSubsystem(master));
  std::printf("%s\n", "Running autonomous");
  std::printf("%d\n", SELECTED_AUTO_NUMBER);


  // Determine which autonomous routine to run
  switch (SELECTED_AUTO_NUMBER) {
    case DO_NOTHING_AUTO:
      doNothingAuto();
      break;
    case LOG_POS_AUTO:

      logPositionAuto(drive);
      break;
    case LOG_VEL_AUTO:
      logVelocityAuto(drive);
      break;
    default:
      doNothingAuto();
      break;
  }

}

void logPositionAuto(std::shared_ptr<DriveSubsystem> drive) {
  std::printf("%s\n", "Running LOG POS");

  CommandRunner::runCommand(CommandFactory::create(new LogPositionCommand(drive, 10)));
}

void logVelocityAuto(std::shared_ptr<DriveSubsystem> drive) {
  CommandRunner::runCommand(CommandFactory::create(new LogVelocityCommand(drive, 10)));
}

void doNothingAuto() {}
