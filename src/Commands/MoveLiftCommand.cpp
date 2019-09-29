#include "user/moveliftcommand.h"
#include <cmath>
#include <math.h>

MoveLiftCommand::MoveLiftCommand(std::shared_ptr<LiftSubsystem> lift, double height, double timeout) : lift(lift)
{
  lift->stop();
  this->height = height;
  this->maxSpeed = maxSpeed;
  this->goalTime = timeout;
}

void MoveLiftCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  this->lift->liftMotors.moveAbsolute(lift->setHeight(height), 300);
}

void MoveLiftCommand::update() {
}

bool MoveLiftCommand::isFinished() {
  double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= goalTime;
  bool reachedDistance = abs(lift->liftMotors.getPosition() -  lift->liftMotors.getTargetPosition()) < 5;
  return reachTimeout || reachedDistance;
}

void MoveLiftCommand::finish() {
  lift->stop();
}
