#include "User/DriveAndIntakeCommand.h"
#include <cmath>
#include <math.h>

DriveAndIntakeCommand::DriveAndIntakeCommand(std::shared_ptr<DriveSubsystem> drive, std::shared_ptr<TraySubsystem> tray,double distance, double maxSpeed) : drive(drive)
  , tray(tray)
{

  tray->reset();

  drive->stop();
  drive->reset();
  this->distance = distance;
  this->maxSpeed = maxSpeed;
}

void DriveAndIntakeCommand::start() {
  tray->intakeCube();
  drive->driveTrain->getModel()->setMaxVelocity(maxSpeed);
  drive->moveInchesAsync(distance);
}

void DriveAndIntakeCommand::update() {

}

bool DriveAndIntakeCommand::isFinished() {
  return drive->driveTrain->isSettled();
}

void DriveAndIntakeCommand::finish() {
  drive->stop();
  tray->stop();
}
