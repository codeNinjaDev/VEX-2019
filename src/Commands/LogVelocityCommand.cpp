#include "user/logvelocitycommand.h"
#include <cmath>
#include <math.h>
LogVelocityCommand::LogVelocityCommand(DriveSubsystem* drive, double timeout)
{
  this->goalTime = timeout;
  this->driveTrain = drive;

  logFile = fopen("/usd/velocityLog.csv", "w");
  fprintf(logFile, "%s,%s\n", "Velocity (Inches/second)", "Time (seconds)");
  pastPosition = 0;
  currentPosition = 0;
  pastTime = 0;
}

void LogVelocityCommand::start() {
  startTime = timer.millis().getValue() / 1000;
  driveTrain->reset();
}

void LogVelocityCommand::update() {
  driveTrain->ArcadeDrive(0, 1, false);
  currentPosition = driveTrain->getLeftEncoder();

  double currentTime = timer.millis().getValue() / 1000;
  double deltaPosition = currentPosition - pastPosition;
  double deltaTime = currentTime - pastTime;
  double velocity = (deltaPosition / deltaTime);

  fprintf(logFile, "%f,%f\n", velocity, currentTime);

  pastTime = currentTime;
  pastPosition = currentPosition;

}

bool LogVelocityCommand::isFinished() {
  double currentTime = timer.millis().getValue() / 1000;
  if (currentTime - startTime >= goalTime) {
    return true;
  }
  // Spin until 100 in
  if ( abs(driveTrain->getLeftEncoder()) >= 100) {
    return true;
  }
}

void LogVelocityCommand::finish() {
  fclose(logFile);
  driveTrain->stop();
}
