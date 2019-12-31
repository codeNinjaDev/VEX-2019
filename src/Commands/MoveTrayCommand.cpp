#include "User/MoveTrayCommand.h"
#include <cmath>
#include <math.h>

MoveTrayCommand::MoveTrayCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TrayPosition position, double maxSpeed) : tray(tray)
{

  this->position = position;
  this->maxSpeed = maxSpeed;
}

void MoveTrayCommand::start() {
  
}

void MoveTrayCommand::update() {
  double currPosition = tray->trayMotor.getPosition();
  tray->moveTray(position, maxSpeed - (90/(double) position)*currPosition);

}

bool MoveTrayCommand::isFinished() {
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 10;
  return hitTarget;
}

void MoveTrayCommand::finish() {
  tray->stop();
}
