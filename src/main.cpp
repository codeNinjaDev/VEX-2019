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
#include "User/MoveArmCommand.h"
#include "User/PIDController.h"
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
  drive->reset();
  pros::delay(2000);


  autoSelector.registerAuto("SMALL_RED_6", SMALL_RED_6);
  autoSelector.registerAuto("SMALL_BLUE_6", SMALL_BLUE_6);
//  autoSelector.registerAuto("SMALL_RED_8_CUBE", SMALL_RED_8_CUBE);
//  autoSelector.registerAuto("SMALL_RED_MANUAL", SMALL_RED_MANUAL);
  autoSelector.registerAuto("ONE Cube",ONE_CUBE_AUTO);
  autoSelector.registerAuto("LARGE_RED_3", LARGE_RED_3); //tested
  autoSelector.registerAuto("LARGE_BLUE_3", LARGE_BLUE_3); //tested
  autoSelector.registerAuto("SMALL_RED_8", SMALL_RED_8);
  autoSelector.registerAuto("SMALL_BLUE_8", SMALL_BLUE_8);
  autoSelector.registerAuto("SKILLS", SKILLS);
  autoSelector.registerAuto("TEST_TURN", TEST_TURN);
  autoSelector.registerAuto("TEST_DISTANCE", TEST_DISTANCE);
  autoSelector.listOptions();
}

void disabled() {
}

void competition_initialize() {
  while (true) {
    SELECTED_AUTO = autoSelector.getSelectedAuto();
    pros::delay(20);
  }
}

void deployTray() {
  tray->cubeScorer.tarePosition();
  tray->outtakeCube(30);
  tray->cubeScorer.moveAbsolute(307, 100);
  pros::delay(700);
  tray->cubeScorer.moveAbsolute(0, 125);
  pros::delay(700);
  tray->outtakeCube(0);

  tray->trayMotor.tarePosition();
  tray->trayMotor.tarePosition();
  drive->initialize();
  drive->rightMotors.tarePosition();
  drive->leftMotors.tarePosition();
}

void scoreTower() {
  pros::delay(250);
  tray->outtakeCube(55);
  pros::delay(1000);
  tray->outtakeCube(0);
}

void turn(double angle, double maxSpeed, double timeout) {
  drive->driveTrain->setMaxVelocity(maxSpeed);
  okapi::Timer timer = okapi::Timer();
  timer.placeMark();

  while((abs(drive->getHeading() - angle) > .5) && ((timer.getDtFromMark().convert(okapi::second)) < (timeout))) {
    double error = (angle - drive->getHeading());
    double kP = 0.013;
    drive->tankDrive(kP*error, -kP*error, false);
    pros::delay(100);
  }
  drive->stop();
}
void stack(){
  tray->outtakeCube(55);
  pros::delay(500);
  tray->outtakeCube(25);

  CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kStack, 75), 3);
  tray->outtakeCube(100);
  drive->driveTrain->setMaxVelocity(100);
  drive->driveTrain->moveDistance(-10_in);
  tray->outtakeCube(0);
  CommandRunner::runCommand(new MoveTrayCommand(tray, TraySubsystem::TrayPosition::kSlant, 100), 3);
  tray->trayMotor.moveVelocity(0);
  pros::delay(500);
  drive->driveTrain->stop();

}

void moveSmallTower() {
  tray->cubeScorer.moveAbsolute(380, 100);
}
void autonomous() {
  tray->reset();
  drive->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  drive->reset();

  switch(SELECTED_AUTO) {
    case DO_NOTHING_AUTO:
      while(true) {
        std::cout << drive->getHeading() << std::flush;
        std::cout << "" << std::flush;

//        std::cout << drive->getLeftEncoder() << std::flush;

        pros::delay(1000);
      break;
    }

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

      case SMALL_RED_6:
        //deploy tray
        drive->reset();
        tray->intakeCube();
        drive->driveTrain->setMaxVelocity(110);
        drive->driveTrain->moveDistance(43_in);
        turn(-19, 100, 0.75);
        drive->driveTrain->setMaxVelocity(50);
        //got cube 1
        drive->driveTrain->moveDistance(7_in);

        drive->driveTrain->moveDistance(-12_in);
        turn(120, 50, 1.0);
        turn(153, 10, 1.5);

        drive->driveTrain->setMaxVelocity(100);
        drive->driveTrain->moveDistance(31_in);
        stack();

        break;
      case SMALL_BLUE_6:
        //deploy tray
        drive->reset();
        tray->intakeCube();
        drive->driveTrain->setMaxVelocity(110);
        drive->driveTrain->moveDistance(43_in);
        turn(19, 100, 0.75);
        drive->driveTrain->setMaxVelocity(50);
        //got cube 1
        drive->driveTrain->moveDistance(7_in);

        drive->driveTrain->moveDistance(-12_in);
        turn(-120, 50, 1.0);
        turn(-153, 10, 1.5);

        drive->driveTrain->setMaxVelocity(100);
        drive->driveTrain->moveDistance(31_in);
        stack();
        pros::delay(15000);
        drive->stop();
      case LARGE_RED_3:
        //deploy tray
        drive->reset();
        tray->intakeCube();
        drive->driveTrain->setMaxVelocity(150);
        drive->driveTrain->moveDistance(48_in);
        turn(29, 80, 1.5);
        //First Cube here
        drive->driveTrain->setMaxVelocity(50);
        drive->driveTrain->moveDistance(8_in);
        turn(0, 80, 1);
        drive->driveTrain->moveDistance(-12_in);
        turn(42, 80, 1.5);
        drive->driveTrain->setMaxVelocity(50);
        drive->driveTrain->moveDistance(20_in);
        drive->driveTrain->moveDistance(-10_in);

        drive->driveTrain->setMaxVelocity(100);
        turn(-140, 80, 1);

        drive->driveTrain->moveDistance(35_in);
        tray->outtakeCube(0);
        stack();
        drive->stop();
        break;
        case PREP_AUTO:
          //deploy tray
          drive->reset();
          tray->intakeCube();
          drive->driveTrain->setMaxVelocity(150);
          drive->driveTrain->moveDistance(48_in);
          turn(35, 80, 1.5);
          //First Cube here
          drive->driveTrain->setMaxVelocity(50);
          drive->driveTrain->moveDistance(8_in);
          drive->driveTrain->setMaxVelocity(100);
          drive->driveTrain->moveDistance(-14_in);
          turn(85, 80, 1.5);
          tray->outtakeCube(50);
          pros::delay(50);
          tray->intakeCube();
          drive->driveTrain->setMaxVelocity(100);
          drive->driveTrain->moveDistance(50_in);

          drive->driveTrain->moveDistance(-12_in);

          drive->driveTrain->turnAngle(144_deg);
          drive->driveTrain->setMaxVelocity(120);
          drive->driveTrain->moveDistance(50_in);
          tray->outtakeCube(0);
          stack();
          drive->stop();
          break;

    case LARGE_BLUE_3:
    //deploy tray
    /*drive->reset();
    tray->intakeCube();
    drive->driveTrain->setMaxVelocity(100);
    drive->driveTrain->moveDistance(22_in);
    turn(90, 80, 2);
    drive->driveTrain->setMaxVelocity(90);
    drive->driveTrain->moveDistance(22_in);
    tray->outtakeCube(0);
    turn(125, 80, 1);
    drive->driveTrain->setMaxVelocity(100);
    drive->driveTrain->moveDistance(12_in);

    stack();*/
    break;

    case TEST_DISTANCE:
      drive->reset();
      drive->driveTrain->setMaxVelocity(40);
      drive->driveTrain->moveDistance(24_in);
      break;

    case TEST_TURN:
      drive->reset();
      turn(90, 150, 1.5);
      break;

    default:
      break;

    case SKILLS:

      deployTray();

//      drive->driveTrain->setState({0_in, 0_in, 0_deg});

      tray->intakeCube();
      pros::delay(800);
      tray->outtakeCube(0);
      pros::delay(200);
      tray->outtakeCube(70);
      pros::delay(500);
      tray->outtakeCube(0);


      drive->driveTrain->setMaxVelocity(75);
      drive->driveTrain->moveDistance(11_in);
      turn(-45, 60, 1);
      drive->driveTrain->moveDistance(20_in);

      moveSmallTower();
      scoreTower();

      drive->driveTrain->moveDistance(-20_in);

      tray->cubeScorer.moveAbsolute(0, 100);
      turn(0, 50, 2);
      pros::delay(250);

      /*drive->driveTrain->setMaxVelocity(35);

      pros::delay(1500);

      drive->driveTrain->setMaxVelocity(35);

//      drive->driveTrain->setState({0_in, 0_in, 0_deg});
      tray->intakeCube();

      drive->driveTrain->setMaxVelocity(75);
//      drive->driveTrain->driveToPoint({0.30_m, 0_m});
      pros::delay(600);
      drive->driveTrain->setMaxVelocity(45);
//      drive->driveTrain->driveToPoint({0.45_m, 0_m});
      pros::delay(600);
      drive->driveTrain->setMaxVelocity(40);
//      drive->driveTrain->driveToPoint({0.50_m, 0_m});
      pros::delay(600);
      tray->outtakeCube(0);

      tray->outtakeCube(40);
      pros::delay(500);

      stack();*/

      drive->driveTrain->stop();
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
