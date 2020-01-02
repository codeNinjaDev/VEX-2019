#include "User/DriveToPointCommand.h"
#include <cmath>
#include <math.h>

DriveToPointCommand::DriveToPointCommand(std::shared_ptr<DriveSubsystem> drive, okapi::QLength forwardCoord, okapi::QLength sideCoord, okapi::QAngle finalHeading) : drive(drive)
{

  drive->stop();
  this->forwardCoord = forwardCoord;
  this->sideCoord = sideCoord;
  this->finalHeading = finalHeading;
}

void DriveToPointCommand::start() {
  drive->driveTrain->getModel()->setMaxVelocity(80);
  drive->driveTrain->driveToPoint({forwardCoord, sideCoord});
  drive->driveTrain->turnToAngle(finalHeading);

}

void DriveToPointCommand::update() {

}

bool DriveToPointCommand::isFinished() {
  return drive->driveTrain->isSettled();
}

void DriveToPointCommand::finish() {
  drive->stop();
}
