#include "main.h"
#include "User/Constants.h"
#include "User/Command.h"
#include "User/CommandRunner.h"
#include "user/CommandFactory.h"
#include "user/DriveSubsystem.h"
#include "user/LiftSubsystem.h"
#include "user/AutoSelector.h"
#include "User/DriveDistanceCommand.h"
int SELECTED_AUTO;

okapi::Controller driver (okapi::ControllerId::master);
okapi::Controller operatorController (okapi::ControllerId::partner);

AutoSelector autoSelector("Do Nothing", DO_NOTHING_AUTO);
std::shared_ptr<DriveSubsystem> drive;
std::shared_ptr<LiftSubsystem> lift;
void initialize() {
  drive.reset(new DriveSubsystem(driver));
  lift.reset(new LiftSubsystem(driver, operatorController));
  lift->reset();

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
  switch(SELECTED_AUTO) {
    case DO_NOTHING_AUTO:
    break;
    case DRIVE_FORWARD_AUTO:
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 20, 1, 5));
      break;
    default:
    break;
  }
}

void opcontrol() {
 	while (true) {
 		std::printf("Running");
 		drive->update();
 		lift->update();
 		pros::delay(20);
 	}
 	drive->stop();
  lift->stop();
 }
