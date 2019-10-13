#include "User/DriveAndIntakeCommand.h"
#include <cmath>
#include <math.h>

DriveAndIntakeCommand::DriveAndIntakeCommand(std::shared_ptr<DriveSubsystem> drive, std::shared_ptr<TraySubsystem> tray,double distance, double maxSpeed, double timeout) : drive(drive)
  , tray(tray)
{

  tray->reset();

  drive->stop();
  drive->reset();
  this->distance = distance;
  this->maxSpeed = maxSpeed;
  this->goalTime = timeout;
}

void DriveAndIntakeCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  tray->intakeCube();
  drive->driveTrain.setMaxVelocity(maxSpeed);
  drive->driveTrain.moveDistanceAsync(distance * (360/(3.1415*BACK_WHEEL_DIAMETER)));
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
