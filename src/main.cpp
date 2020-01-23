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
#include "User/MoveArmCommand.h"

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
  drive->resetGyro();
  autoSelector.registerAuto("SMALL_RED_8_CUBE", SMALL_RED_8_CUBE);
  autoSelector.registerAuto("ONE Cube",ONE_CUBE_AUTO);
  autoSelector.registerAuto("SMALL_RED_MANUAL", SMALL_RED_MANUAL);
  autoSelector.registerAuto("SMALL_RED_6", SMALL_RED_6);
  autoSelector.registerAuto("SMALL_BLUE_6", SMALL_BLUE_6);
  autoSelector.registerAuto("LARGE_RED_4", LARGE_RED_4);
  autoSelector.registerAuto("LARGE_BLUE_4", LARGE_BLUE_4);
  autoSelector.registerAuto("SKILLS_RUN", SKILLS_RUN);
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
        std::cout << drive->getHeading() << std::flush;
        std::cout << "" << std::flush;

        pros::delay(1000);
      }
      break;
    case SMALL_RED_8_CUBE:
      tray->reset();
      CommandRunner::runCommand(new MoveArmCommand(tray, TraySubsystem::TowerPosition::kLowTower, 100), 1);
      CommandRunner::runCommand(new MoveArmCommand(tray, TraySubsystem::TowerPosition::kIntake, 100), 2);

      tray->trayMotor.tarePosition();
      drive->initialize();
      drive->leftMotors.tarePosition();
      drive->rightMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      drive->driveTrain->turnToAngle(-8_deg);
      tray->intakeCube();
      drive->driveTrain->setMaxVelocity(60);
      drive->driveTrain->driveToPoint({0.4_m, 0_m});
      drive->driveTrain->turnAngle(-15_deg);
      tray->outtakeCube(0);
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(-15_in);
      drive->driveTrain->setMaxVelocity(75);
      tray->intakeCube();
      drive->driveTrain->turnToAngle(1.92_deg);
      drive->driveTrain->driveToPoint({0.4_m, 0.1_m});
      tray->outtakeCube(0);
      drive->driveTrain->turnAngle({64.6_deg});
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(15.3_in);

      tray->trayMotor.moveRelative((double) TraySubsystem::TrayPosition::kStack, 75);
      pros::delay(1000);
      tray->outtakeCube(0);


      CommandRunner::runCommand(new DriveDistanceCommand(drive, -4, 40), 1);
      tray->trayMotor.moveRelative(-(double) TraySubsystem::TrayPosition::kStack, 100);
      pros::delay(2000);
      tray->trayMotor.moveVelocity(0);
      break;
    case ONE_CUBE_AUTO:
      CommandRunner::runCommand(new DriveDistanceCommand(drive, -8, 40), 1);
      CommandRunner::runCommand(new DriveDistanceCommand(drive, 8, 40), 1);
      break;
    default:
      break;
    case SMALL_RED_6:
      tray->trayMotor.tarePosition();
      drive->initialize();
      drive->leftMotors.tarePosition();
      drive->rightMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();
      drive->driveTrain->setMaxVelocity(60);
      drive->driveTrain->driveToPoint({0.45_m, 0_m});
      drive->driveTrain->moveDistance(-3_in);
      drive->driveTrain->turnAngle(-8_deg);
      drive->driveTrain->moveDistance(4_in);
      pros::delay(1000);
      tray->outtakeCube(0);
      drive->driveTrain->moveDistance(-4_in);
      drive->driveTrain->setMaxVelocity(40);
      drive->driveTrain->turnAngle(8_deg);
      drive->driveTrain->setMaxVelocity(90);
      drive->driveTrain->moveDistance(-7.5_in);
      drive->driveTrain->turnAngle(50_deg);
      drive->driveTrain->setMaxVelocity(40);
      drive->driveTrain->moveDistance(5_in);
      tray->outtakeCube(40);
      pros::delay(500);


      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
      drive->driveTrain->moveDistance(-4_in);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 75), 3);

      //pros::delay(1000);
      //tray->outtakeCube(100);


      //back up
      //drive->driveTrain->moveDistance(-5_in);
      //tray->outtakeCube(0);

      //put tray down
      //tray->trayMotor.moveRelative((double) TraySubsystem::TrayPosition::kSlant, 90);

      /*
        drive->driveTrain->setMaxVelocity(60);
        drive->driveTrain->moveDistance(5_in);
        pros::delay(75);
        tray->outtakeCube(0);
        drive->driveTrain->moveDistance(-15_in);
        drive->driveTrain->turnAngle(55_deg);
        drive->driveTrain->moveDistance(2_in);
        tray->trayMotor.moveRelative(-(double) TraySubsystem::TrayPosition::kStack, 100);
        pros::delay(2000);
        tray->trayMotor.moveVelocity(0);
      */

      break;
    case SMALL_BLUE_6:
      //same as SMALL_RED_5 but reverse turns
      break;

    case LARGE_RED_4:
      //uncomment one block at a time

      //gets cube 2
      drive->driveTrain->setMaxVelocity(45);
      drive->driveTrain->moveDistance(15_in);

      //turn towards cube 3 and 4
      //drive->driveTrain->setMaxVelocity(30);
      //drive->driveTrain->turnAngle(90_deg);

      //gets cubes 3 and 4
      //drive->driveTrain->setMaxVelocity(45);
      //drive->driveTrain->moveDistance(30_in);
      //tray->outtakeCube(0);

      //align to wall
      //drive->driveTrain->setMaxVelocity(60);
      //drive->driveTrain->moveDistance(-40_in);

      //turn towards zone
      //drive->driveTrain->setMaxVelocity(30);
      //drive->driveTrain->turnAngle(90_deg);

      //go to stacking position
      //drive->driveTrain->setMaxVelocity(40);
      //drive->driveTrain->moveDistance(3_in);

      //back up
      //drive->driveTrain->moveDistance(-5_in);
      //tray->outtakeCube(0);

      //put tray down
      //tray->trayMotor.moveRelative((double) TraySubsystem::TrayPosition::kSlant, 90);

      break;
    case LARGE_BLUE_4:
      //same as LARGE_RED_4 but reverse turns
      break;
    case SKILLS_RUN:
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
