#include "User/DriveDistanceCommand.h"
#include <cmath>
#include <math.h>

DriveDistanceCommand::DriveDistanceCommand(std::shared_ptr<DriveSubsystem> drive, double distance, double maxSpeed, double timeout) : drive(drive)
{
  drive->stop();
  drive->reset();
  this->distance = distance;
  this->maxSpeed = maxSpeed;
  this->goalTime = timeout;
}

void DriveDistanceCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  drive->driveTrain.setMaxVelocity(maxSpeed);
  drive->driveTrain.moveDistanceAsync(distance * (360/(3.1415*BACK_WHEEL_DIAMETER)));
  drive->driveTrain.waitUntilSettled();

}

void DriveDistanceCommand::update() {
  //drive->arcadeDrive(maxSpeed, 0, false);
}

bool DriveDistanceCommand::isFinished() {
  return true;
  /*double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= goalTime;
  bool reachedDistance = ((drive->getLeftEncoder() + drive->getRightEncoder()) / 2) >= distance;
  return reachTimeout || reachedDistance;*/
}

void DriveDistanceCommand::finish() {

  drive->stop();
}
