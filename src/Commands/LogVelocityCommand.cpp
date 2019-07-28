#include "user/logvelocitycommand.h"
#include <cmath>
#include <math.h>
LogVelocityCommand::LogVelocityCommand(std::unique_ptr<DriveSubsystem> drive, double timeout) : driveTrain(std::move(drive))
{
  this->goalTime = timeout;

  logFile = fopen("/usd/velocityLog.csv", "w");
  fprintf(logFile, "%s,%s\n", "Velocity (Inches/second)", "Time (seconds)");
  pastPosition = 0;
  currentPosition = 0;
  pastTime = 0;
}

void LogVelocityCommand::start() {
  startTime = timer.millis().convert(okapi::millisecond);
  driveTrain->reset();
}

void LogVelocityCommand::update() {
  driveTrain->ArcadeDrive(0, 1, false);
  currentPosition = driveTrain->getLeftEncoder();

  double currentTime =  timer.millis().convert(okapi::millisecond) - startTime;
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
