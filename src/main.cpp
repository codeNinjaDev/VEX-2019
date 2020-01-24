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
//  autoSelector.registerAuto("SMALL_RED_8_CUBE", SMALL_RED_8_CUBE);
//  autoSelector.registerAuto("SMALL_RED_MANUAL", SMALL_RED_MANUAL);
  autoSelector.registerAuto("ONE Cube",ONE_CUBE_AUTO);
  autoSelector.registerAuto("SMALL_RED_5", SMALL_RED_5);
  autoSelector.registerAuto("SMALL_BLUE_5", SMALL_BLUE_5);
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
/*
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
*/

    case ONE_CUBE_AUTO:
      tray->cubeScorer.tarePosition();
      tray->cubeScorer.moveAbsolute(307, 100);
      pros::delay(700);
      tray->cubeScorer.moveAbsolute(0, 125);
      pros::delay(1000);

      drive->driveTrain->setMaxVelocity(65);
      drive->driveTrain->moveDistance(6_in);
      drive->driveTrain->moveDistance(-6_in);
      break;

    default:
      break;

    case SMALL_RED_6:
      tray->cubeScorer.tarePosition();
      tray->cubeScorer.moveAbsolute(307, 100);
      pros::delay(700);
      tray->cubeScorer.moveAbsolute(0, 125);
      pros::delay(700);

      tray->trayMotor.tarePosition();
      drive->rightMotors.tarePosition();
      drive->initialize();
      drive->leftMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->driveToPoint({0.30_m, 0_m});
      pros::delay(600);
      drive->driveTrain->setMaxVelocity(45);
      drive->driveTrain->driveToPoint({0.45_m, 0_m});
      drive->driveTrain->setMaxVelocity(140);
      drive->driveTrain->moveDistance(-10.5_in);
      drive->driveTrain->setMaxVelocity(80);
      drive->driveTrain->turnAngle(53_deg);
      drive->driveTrain->setMaxVelocity(50);
      drive->driveTrain->moveDistance(5_in);
      tray->outtakeCube(40);
      pros::delay(500);

      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(-4_in);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 175), 3);
      break;

    case SMALL_BLUE_6:
      tray->cubeScorer.tarePosition();
      tray->cubeScorer.moveAbsolute(307, 100);
      pros::delay(700);
      tray->cubeScorer.moveAbsolute(0, 125);
      pros::delay(700);

      tray->trayMotor.tarePosition();
      drive->initialize();
      drive->rightMotors.tarePosition();
      drive->leftMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->driveToPoint({0.30_m, 0_m});
      pros::delay(600);
      drive->driveTrain->setMaxVelocity(45);
      drive->driveTrain->driveToPoint({0.45_m, 0_m});
      drive->driveTrain->setMaxVelocity(140);
      drive->driveTrain->moveDistance(-10.5_in);
      drive->driveTrain->setMaxVelocity(80);
      drive->driveTrain->turnAngle(-53_deg);
      drive->driveTrain->setMaxVelocity(50);
      drive->driveTrain->moveDistance(5_in);
      tray->outtakeCube(40);
      pros::delay(500);

      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(-4_in);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 175), 3);
      break;

    case LARGE_RED_4:
      tray->cubeScorer.tarePosition();
      tray->cubeScorer.moveAbsolute(307, 100);
      pros::delay(700);
      tray->cubeScorer.moveAbsolute(0, 125);
      pros::delay(700);

      tray->trayMotor.tarePosition();
      drive->initialize();
      drive->rightMotors.tarePosition();
      drive->leftMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->driveToPoint({0.15_m, 0_m});
      pros::delay(600);

      drive->driveTrain->setMaxVelocity(35);
      drive->driveTrain->turnAngle(-35_deg);

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->moveDistance(11_in);

      pros::delay(750);
      tray->outtakeCube(0);
      pros::delay(750);

      drive->driveTrain->moveDistance(-12_in);

      drive->driveTrain->setMaxVelocity(35);
      drive->driveTrain->turnAngle(-55_deg);

      tray->outtakeCube(40);
      pros::delay(500);

      drive->driveTrain->setMaxVelocity(40);
      drive->driveTrain->moveDistance(4_in);

      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(-4_in);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 175), 3);
      break;

    case LARGE_BLUE_4:
      tray->cubeScorer.tarePosition();
      tray->cubeScorer.moveAbsolute(307, 100);
      pros::delay(700);
      tray->cubeScorer.moveAbsolute(0, 125);
      pros::delay(700);

      tray->trayMotor.tarePosition();
      drive->initialize();
      drive->rightMotors.tarePosition();
      drive->leftMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->driveToPoint({0.15_m, 0_m});
      pros::delay(600);

      drive->driveTrain->setMaxVelocity(35);
      drive->driveTrain->turnAngle(-35_deg);

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->moveDistance(11_in);

      pros::delay(750);
      tray->outtakeCube(0);
      pros::delay(750);

      drive->driveTrain->moveDistance(-12_in);

      drive->driveTrain->setMaxVelocity(35);
      drive->driveTrain->turnAngle(-55_deg);

      tray->outtakeCube(40);
      pros::delay(500);

      drive->driveTrain->setMaxVelocity(40);
      drive->driveTrain->moveDistance(4_in);

      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(-4_in);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 175), 3);
      break;

    case SKILLS_RUN:
      tray->cubeScorer.tarePosition();
      tray->cubeScorer.moveAbsolute(307, 100);
      pros::delay(700);
      tray->cubeScorer.moveAbsolute(0, 125);
      pros::delay(700);

      tray->trayMotor.tarePosition();
      drive->initialize();
      drive->rightMotors.tarePosition();
      drive->leftMotors.tarePosition();
      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();

      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->driveToPoint({0.30_m, 0_m});
      pros::delay(600);
      drive->driveTrain->setMaxVelocity(45);
      drive->driveTrain->driveToPoint({0.45_m, 0_m});
      drive->driveTrain->setMaxVelocity(140);
      drive->driveTrain->moveDistance(-10.5_in);
      drive->driveTrain->setMaxVelocity(80);
      drive->driveTrain->turnAngle(53_deg);
      drive->driveTrain->setMaxVelocity(50);
      drive->driveTrain->moveDistance(5_in);
      tray->outtakeCube(40);
      pros::delay(500);

      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
      drive->driveTrain->setMaxVelocity(100);
      drive->driveTrain->moveDistance(-4_in);
      CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 175), 3);
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
