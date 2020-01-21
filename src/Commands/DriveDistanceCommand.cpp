#include "User/DriveDistanceCommand.h"
#include <cmath>
#include <math.h>

DriveDistanceCommand::DriveDistanceCommand(std::shared_ptr<DriveSubsystem> drive, double distance, double maxSpeed) : drive(drive)
{
  drive->stop();
  drive->reset();
  this->distance = distance;
  this->maxSpeed = maxSpeed;
}

void DriveDistanceCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  drive->driveTrain->setMaxVelocity(maxSpeed);
  drive->moveInchesAsync(distance);

}

void DriveDistanceCommand::update() {
  //drive->arcadeDrive(maxSpeed, 0, false);
}

bool DriveDistanceCommand::isFinished() {
  return drive->driveTrain->isSettled();
}

void DriveDistanceCommand::finish() {

  drive->stop();
}
