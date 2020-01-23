#include "User/DriveTurnCommand.h"
#include <cmath>
#include <math.h>

DriveTurnCommand::DriveTurnCommand(std::shared_ptr<DriveSubsystem> drive, double angle, double kP, bool absolute, double maxSpeed) : drive(drive)
{

  drive->stop();
  this->offset = drive->getHeading();
  if (absolute)
    this->angle = angle;
  else
    this->angle = angle + offset;
  this->maxSpeed = maxSpeed;
}

void DriveTurnCommand::start() {
  drive->driveTrain->getModel()->setMaxVelocity(maxSpeed);

}

void DriveTurnCommand::update() {
  double error = angle - drive->getHeading();
  drive->arcadeDrive(0, -kP * error, false);
}

bool DriveTurnCommand::isFinished() {
  double error = angle - drive->getHeading();
  if (abs(error) < 3) {
    return true;
  }
  return false;
}

void DriveTurnCommand::finish() {
  drive->stop();
}
