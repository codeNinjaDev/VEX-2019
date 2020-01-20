#include "User/MoveTrayCommand.h"
#include <cmath>
#include <math.h>

MoveTrayCommand::MoveTrayCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TrayPosition position, double maxSpeed) : tray(tray)
{

  this->position = position;
  this->maxSpeed = maxSpeed;
}

void MoveTrayCommand::start() {
  tray->moveTray(position, maxSpeed,true);

}

void MoveTrayCommand::update() {
  tray->moveTray(position, maxSpeed,true);

}

bool MoveTrayCommand::isFinished() {
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 10;
  return hitTarget;
}

void MoveTrayCommand::finish() {
  tray->stop();
}
