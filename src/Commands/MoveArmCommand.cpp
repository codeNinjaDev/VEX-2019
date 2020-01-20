#include "User/MoveArmCommand.h"
#include <cmath>
#include <math.h>

MoveArmCommand::MoveArmCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TowerPosition position, double maxSpeed) : tray(tray)
{
  this->tray = tray;
  this->position = position;
  this->maxSpeed = maxSpeed;
}

void MoveArmCommand::start() {

}

void MoveArmCommand::update() {
  tray->scoreTower(position, maxSpeed);

}

bool MoveArmCommand::isFinished() {
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 10;
  return hitTarget;
}

void MoveArmCommand::finish() {
  tray->stop();
}
