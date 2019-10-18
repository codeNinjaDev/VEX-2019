#include "main.h"
#include "User/Constants.h"
#include "User/Command.h"
#include "User/CommandRunner.h"
#include "User/CommandFactory.h"
#include "User/DriveSubsystem.h"
#include "User/TraySubsystem.h"
#include "User/AutoSelector.h"
#include "User/DriveDistanceCommand.h"
#include "User/DriveAndIntakeCommand.h"
#include "User/DriveTurnCommand.h"
#include "User/MoveTrayCommand.h"
#include "User/IntakeCommand.h"

int SELECTED_AUTO;

okapi::Controller driver (okapi::ControllerId::master);
okapi::Controller operatorController (okapi::ControllerId::partner);

AutoSelector autoSelector("Do Nothing", DO_NOTHING_AUTO);
std::shared_ptr<DriveSubsystem> drive;
std::shared_ptr<TraySubsystem> tray;

void initialize() {
  drive.reset(new DriveSubsystem(driver));
  tray.reset(new TraySubsystem(driver, operatorController));
  autoSelector.registerAuto("SMALL RED ZONE", SMALL_RED);
  autoSelector.registerAuto("SMALL BLUE ZONE", SMALL_BLUE);
  autoSelector.registerAuto("LARGE RED ZONE", LARGE_RED);
  autoSelector.registerAuto("LARGE BLUE ZONE", LARGE_BLUE);
  autoSelector.registerAuto("SKILLS RUN", SKILLS_RUN);
  autoSelector.registerAuto("DRIVE FORWARD AUTO", DRIVE_FORWARD_AUTO);
  autoSelector.listOptions();
}


void disabled() {}


void competition_initialize() {
  while (true) {
    SELECTED_AUTO = autoSelector.getSelectedAuto();
    pros::delay(20);
  }
}

void autonomous() {
  tray->reset();
  drive->reset();
  switch(SELECTED_AUTO) {
    case DO_NOTHING_AUTO:
      break;
    case SMALL_RED:
      //works most consistantly
      CommandRunner::runCommand(new IntakeCommand(tray, 100, 1));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 48, 70, 3));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, -44.5, 100, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 115, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 3.5, 100, 3));
      CommandRunner::runCommand(new IntakeCommand(tray, -100, .65));
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 60, 2.5));
      pros::delay(100);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, .5, 100, 1));
      pros::delay(250);
      CommandRunner::runCommand(new DriveTurnCommand(drive, 10, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -15, 105, 3));
      break;
    case SMALL_BLUE:
      //should work with timeout
      CommandRunner::runCommand(new IntakeCommand(tray, 100, .5));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 48, 70, 3));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, -44.5, 100, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -115, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 3.5, 100, 3));
      CommandRunner::runCommand(new IntakeCommand(tray, -100, .65));
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 60, 2.5));
      pros::delay(100);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, .5, 100, 1));
      pros::delay(250);
      CommandRunner::runCommand(new DriveTurnCommand(drive, -45, 75, 1));
      pros::delay(100);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kPartialStack, 60, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -15, 105, 3));
      break;
    case LARGE_RED:
      //should work with timeout
      CommandRunner::runCommand(new IntakeCommand(tray, 100, .5));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 48, 70, 3));
      CommandRunner::runCommand(new IntakeCommand(tray, 100, .6));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -138, 60, 1));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 43, 70, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 5, 100, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 5, 90, 3));
      CommandRunner::runCommand(new IntakeCommand(tray, -100, .6));
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 60, 2.5));
      pros::delay(100);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -30, 90, 3));
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 100, 2.5));
      break;
    case LARGE_BLUE:
      //should work with timeout
      CommandRunner::runCommand(new IntakeCommand(tray, 100, .5));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 48, 70, 3));
      CommandRunner::runCommand(new IntakeCommand(tray, 100, .6));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 138, 60, 1));
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 43, 70, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -5, 100, 1));
      CommandRunner::runCommand(new IntakeCommand(tray, -100, .6));
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 60, 2.5));
      pros::delay(100);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -30, 90, 3));
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 100, 2.5));
      break;
    case SKILLS_RUN:
      //hasn't been tested or changed since Monday
      CommandRunner::runCommand(new DriveAndIntakeCommand(drive, tray, 100, 105, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -40, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -15, 105, 3));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 20, 105, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -45, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -23, 105, 3));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 6, 105, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 180, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 14, 105, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 10, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -30, 105, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -50, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 60, 105, 3));
      break;
    case DRIVE_FORWARD_AUTO:
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 12, 200, 3));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -12, 200, 3));
      break;
    default:
      break;
  }
  tray->stop();
  drive->stop();
}

void opcontrol() {
 	while (true) {
 		std::printf("Running");
 		drive->update();
    tray->update();
 		pros::delay(20);
 	}
  tray->stop();
 	drive->stop();
 }
