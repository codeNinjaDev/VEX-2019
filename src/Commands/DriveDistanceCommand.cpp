#include "User/DriveDistanceCommand.h"
#include "User/PIDController.h"

#include <cmath>
#include <math.h>

DriveDistanceCommand::DriveDistanceCommand(std::shared_ptr<DriveSubsystem> drive, double distance, double maxSpeed) : drive(drive), pid(0.5, 0, 0, 20)
{
  drive->stop();
  drive->reset();
  this->distance = distance;
  this->maxSpeed = maxSpeed;
  pid.SetSetpoint(distance);
  drive->reset();
}

void DriveDistanceCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  drive->driveTrain->setMaxVelocity(maxSpeed);
  drive->arcadeDrive(pid.Calculate(drive->backLeftDriveMotor.getPosition() * (4*3.1415) * (1 / 360)), 0, false);
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
