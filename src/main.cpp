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

int SELECTED_AUTO;

okapi::Controller driver (okapi::ControllerId::master);
okapi::Controller operatorController (okapi::ControllerId::partner);

AutoSelector autoSelector("Do Nothing", DO_NOTHING_AUTO);
std::shared_ptr<DriveSubsystem> drive;
std::shared_ptr<TraySubsystem> tray;

void initialize() {
  drive.reset(new DriveSubsystem(driver));
  tray.reset(new TraySubsystem(driver, operatorController));
  autoSelector.registerAuto("DRIVE FORWARD AUTO", DRIVE_FORWARD_AUTO);
  autoSelector.registerAuto("SMALL RED ZONE", SMALL_RED);
  autoSelector.registerAuto("SMALL BLUE ZONE", SMALL_BLUE);
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
    case DRIVE_FORWARD_AUTO:
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 48, 200, 3));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -46, 200, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 110, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 25, 100, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, -90, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 48, 200, 3));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -46, 200, 3));
      CommandRunner::runCommand(new DriveTurnCommand(drive, 110, 75, 1));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 15, 100, 3));
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -10, 100, 3));
      break;
    case SMALL_RED:
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 100, 105, 3));
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
