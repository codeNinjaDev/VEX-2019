#include "User/IntakeCommand.h"
#include <cmath>
#include <math.h>

IntakeCommand::IntakeCommand(std::shared_ptr<TraySubsystem> tray, double intakeSpeed, double timeout) : tray(tray)
{
  this->intakeSpeed = intakeSpeed;
  this->goalTime = timeout;
}

void IntakeCommand::start() {
  tray->outtakeCube(-intakeSpeed);
  pros::delay(1000*goalTime);
}

void IntakeCommand::update() {

}

bool IntakeCommand::isFinished() {
  return true;
}

void IntakeCommand::finish() {
  tray->stop();
}
