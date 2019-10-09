#include "User/MoveTrayCommand.h"
#include <cmath>
#include <math.h>

MoveTrayCommand::MoveTrayCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TrayPosition position, double timeout) : tray(tray)
{

  this->position = position;
  this->goalTime = timeout;
}

void MoveTrayCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  tray->moveTray(position, 100);
}

void MoveTrayCommand::update() {

}

bool MoveTrayCommand::isFinished() {
  double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= goalTime;
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 3;
  return reachTimeout || hitTarget;
}

void MoveTrayCommand::finish() {
  tray->stop();
}
