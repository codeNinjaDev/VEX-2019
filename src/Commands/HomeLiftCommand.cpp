#include "user/homeliftcommand.h"
#include <cmath>
#include <math.h>

HomeLiftCommand::HomeLiftCommand(std::shared_ptr<LiftSubsystem> lift, double timeout) : lift(lift)
{
  lift->stop();
  lift->reset();
  this->goalTime = timeout;
}

void HomeLiftCommand::start() {
  this->startTime = (timer.millis().getValue() / 1000);
}

void HomeLiftCommand::update() {}

bool HomeLiftCommand::isFinished() {
  double currentTime = (timer.millis().getValue() / 1000);
  bool reachTimeout = (currentTime  - startTime) >= goalTime;
  return lift->home() || reachTimeout;
}

void HomeLiftCommand::finish() {
  lift->stop();
}
