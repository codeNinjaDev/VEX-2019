#include "User/DriveTurnCommand.h"
#include <cmath>
#include <math.h>

DriveTurnCommand::DriveTurnCommand(std::shared_ptr<DriveSubsystem> drive, double angle, double maxSpeed) : drive(drive)
{

  drive->stop();
  this->angle = angle;
  this->maxSpeed = maxSpeed;
}

void DriveTurnCommand::start() {
  drive->driveTrain->getModel()->setMaxVelocity(maxSpeed);
  drive->turnAngleAsync(angle);
}

void DriveTurnCommand::update() {

}

bool DriveTurnCommand::isFinished() {
  return drive->driveTrain->isSettled();
;
}

void DriveTurnCommand::finish() {
  drive->stop();
}
