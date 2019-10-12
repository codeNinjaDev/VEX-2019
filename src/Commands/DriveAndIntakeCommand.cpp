#include "User/DriveAndIntakeCommand.h"
#include <cmath>
#include <math.h>

DriveAndIntakeCommand::DriveAndIntakeCommand(std::shared_ptr<DriveSubsystem> drive, std::shared_ptr<TraySubsystem> tray,double distance, double timeout) : drive(drive)
  , tray(tray)
{

  tray->reset();

  drive->stop();
  drive->reset();
  this->distance = distance;
  this->goalTime = timeout;
}

void DriveAndIntakeCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  tray->intakeCube();
  drive->moveInchesAsync(distance);
  drive->driveTrain.waitUntilSettled();
}

void DriveAndIntakeCommand::update() {

}

bool DriveAndIntakeCommand::isFinished() {
  /*double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= goalTime;
  bool reachedDistance = ((drive->getLeftEncoder() + drive->getRightEncoder()) / 2) >= distance;*/
  return true;
}

void DriveAndIntakeCommand::finish() {
  drive->stop();
  tray->stop();
}
