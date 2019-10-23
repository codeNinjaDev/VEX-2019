#include "User/MoveTrayCommand.h"
#include <cmath>
#include <math.h>

MoveTrayCommand::MoveTrayCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TrayPosition position, double maxSpeed, double timeout) : tray(tray)
{

  this->position = position;
  this->maxSpeed = maxSpeed;
  this->timeout = timeout;
}

void MoveTrayCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  tray->moveTray(position, maxSpeed);
}

void MoveTrayCommand::update() {

}

bool MoveTrayCommand::isFinished() {
  double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= timeout;
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 35;
  return reachTimeout || hitTarget;
}

void MoveTrayCommand::finish() {
  tray->stop();
}
