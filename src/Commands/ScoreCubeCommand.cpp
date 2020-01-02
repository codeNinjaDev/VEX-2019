#include "User/ScoreCubeCommand.h"
#include <cmath>
#include <math.h>

ScoreCubeCommand::ScoreCubeCommand(std::shared_ptr<TraySubsystem> tray, TraySubsystem::TowerPosition position, double maxSpeed) : tray(tray)
{
  this->position = position;
  this->maxSpeed = maxSpeed;
}

void ScoreCubeCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
  tray->scoreTower(TraySubsystem::TowerPosition::kLowTower, 50);
}

void ScoreCubeCommand::update() {

}

bool ScoreCubeCommand::isFinished() {
  bool hitTarget = abs(tray->trayMotor.getTargetPosition() - tray->trayMotor.getPosition()) < 3;
  return hitTarget;
}

void ScoreCubeCommand::finish() {
  tray->scoreTower(TraySubsystem::TowerPosition::kIntake, 50);
  tray->stop();
}
