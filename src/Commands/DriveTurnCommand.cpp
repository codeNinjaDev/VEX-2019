#include "User/DriveTurnCommand.h"
#include <cmath>
#include <math.h>

DriveTurnCommand::DriveTurnCommand(std::shared_ptr<DriveSubsystem> drive, double angle, double maxSpeed, double timeout) : drive(drive)
{

  drive->stop();
  this->angle = angle;
  this->maxSpeed = maxSpeed;
  this->goalTime = timeout;
}

void DriveTurnCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  drive->driveTrain.setMaxVelocity(maxSpeed);
  drive->turnDegrees((380/180) * angle);
  drive->driveTrain.waitUntilSettled();
}

void DriveTurnCommand::update() {

}

bool DriveTurnCommand::isFinished() {

  return true;
}

void DriveTurnCommand::finish() {
  drive->stop();
}
