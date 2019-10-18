#include "User/ScoreCubeCommand.h"
#include <cmath>
#include <math.h>

ScoreCubeCommand::ScoreCubeCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TowerPosition position, double maxSpeed, double timeout) : tray(tray)
{

  this->position = position;
  this->maxSpeed = maxSpeed;
  this->timeout = timeout;
}

void ScoreCubeCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  tray->scoreTower(TraySubsystem::TowerPosition::kLowTower, 50);
}

void ScoreCubeCommand::update() {

}

bool ScoreCubeCommand::isFinished() {
  double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= timeout;
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 3;
  return reachTimeout || hitTarget;
}

void ScoreCubeCommand::finish() {
  tray->scoreTower(TraySubsystem::TowerPosition::kTray, 50);
  tray->stop();
}
