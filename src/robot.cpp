#include "main.h"
#include "User/AutoSelector.h"
#include "User/Constants.h"

#include "user/Command.h"
#include "user/CommandRunner.h"
#include "user/CommandFactory.h"
#include "user/DriveSubsystem.h"
#include "user/LogVelocityCommand.h"
#include "user/LogPositionCommand.h"
#include "user/HomeLiftCommand.h"

#include "User/Constants.h"

int SELECTED_AUTO_NUMBER;
// Initialize autoSelector and set default values
AutoSelector autoSelector("Do Nothing", DO_NOTHING_AUTO);
okapi::Controller master;
std::shared_ptr<DriveSubsystem> drive (new DriveSubsystem(master));
std::shared_ptr<LiftSubsystem> lift (new LiftSubsystem(master));

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lift->initialize();
	// Register the rest of the autonomous routines
	autoSelector.registerAuto("Log Position RED", LOG_POS_AUTO);
	autoSelector.registerAuto("Log Velocity RED", LOG_VEL_AUTO);
	// Create the dropdown
	autoSelector.listOptions();


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	SELECTED_AUTO_NUMBER = autoSelector.getSelectedAuto();

}


void autonomous() {

  std::printf("%s\n", "Running autonomous");
  std::printf("%d\n", SELECTED_AUTO_NUMBER);

  // Determine which autonomous routine to run
  switch (SELECTED_AUTO_NUMBER) {
    case DO_NOTHING_AUTO:
      break;
    case LOG_POS_AUTO:
			// Drive for 10 seconds
			CommandRunner::runCommand(new LogPositionCommand(drive, 10));
      break;
    case LOG_VEL_AUTO:
			CommandRunner::runCommand(new LogVelocityCommand(drive, 10));
      break;
		case HOME_LIFT_AUTO:
			CommandRunner::runCommand(new HomeLiftCommand(lift, 5));
			break;
    default:
      break;
  }

}


void opcontrol() {

	while (true) {
		drive->update();
		lift->update();
		pros::delay(20);
	}
	drive->stop();

}
