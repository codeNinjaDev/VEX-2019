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
#include "User/DriveToPointCommand.h"

int SELECTED_AUTO;

okapi::Controller driver (okapi::ControllerId::master);
okapi::Controller operatorController (okapi::ControllerId::partner);

AutoSelector autoSelector("Do Nothing", DO_NOTHING_AUTO);
std::shared_ptr<DriveSubsystem> drive;
std::shared_ptr<TraySubsystem> tray;

void initialize() {
  okapi::Logger::setDefaultLogger(
    std::make_shared<okapi::Logger>(
        okapi::TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        okapi::Logger::LogLevel::warn // Show errors and warnings
    )
);

  drive.reset(new DriveSubsystem(driver));
  tray.reset(new TraySubsystem(driver, operatorController));
  autoSelector.registerAuto("SMALL_RED", SMALL_RED);
  autoSelector.registerAuto("ONE Cube",ONE_CUBE_AUTO);
  autoSelector.registerAuto("SMALL_RED_MANUAL", SMALL_RED_MANUAL);
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
      while(true) {
        std::cout << drive->driveTrain->getState().str() << std::flush;
        pros::delay(1000);
      }
      break;
    case SMALL_RED:
      drive->initialize();
      //CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 100), 1);
      tray->intakeCube();
      drive->driveTrain->getModel()->setMaxVelocity(50);
      drive->driveTrain->driveToPoint({12_in, 0_in});
      drive->driveTrain->turnToAngle(-45_deg);
      drive->driveTrain->driveToPoint({4_in, 3_in});
      drive->driveTrain->turnToAngle(0_deg);
      drive->driveTrain->driveToPoint({12_in, 3_in});
      drive->driveTrain->turnToPoint({0_in, 0_in});
      drive->driveTrain->driveToPoint({0_in, 0_in});
      tray->outtakeCube(0);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 100), 2);


      tray->outtakeCube(0);
      pros::delay(1000);
      CommandRunner::runCommand(new DriveToPointCommand(drive, 0_in, 20_in, 45_deg, false), 1);
      pros::delay(1000);

      //  CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 60), 2);
      CommandRunner::runCommand(new IntakeCommand(tray, -10, .65), 0.65);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -4, 40), 1);
      break;
    case SMALL_RED_MANUAL:
      tray->intakeCube();
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 12, 10), 1.5);
      CommandRunner::runCommand(new DriveTurnCommand(drive, 65, 40), 1.5);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 18, 10), 1.5);
      tray->outtakeCube(0);

      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 60), 2);

      CommandRunner::runCommand(new DriveDistanceCommand(drive, -12, 40), 1.5);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 15, 40), 1.5);

      break;
    case ONE_CUBE_AUTO:
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -8, 40), 1);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 8, 40), 1);
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
