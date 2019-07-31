#include "user/logpositioncommand.h"
#include <cmath>
#include <math.h>
LogPositionCommand::LogPositionCommand(std::shared_ptr<DriveSubsystem> drive, double timeout) : driveTrain(drive)
{
  this->goalTime = timeout;

  logFile = fopen("/usd/position.csv", "w");
  fprintf(logFile, "%s,%s\n", "Position (Inches)", "Time (seconds)");
  currentPosition = 0;
}

void LogPositionCommand::start() {

  startTime = timer.millis().convert(okapi::millisecond);
  driveTrain->reset();
}

void LogPositionCommand::update() {
  driveTrain->ArcadeDrive(0, 1, false);
  currentPosition = driveTrain->getLeftEncoder();

  double currentTime = timer.millis().convert(okapi::millisecond) - startTime;

  fprintf(logFile, "%f,%f\n", currentPosition, currentTime);


}

bool LogPositionCommand::isFinished() {
  double currentTime = timer.millis().getValue() / 1000;
  if (currentTime - startTime >= goalTime) {
    return true;
  }
  // Spin until 100 in
  if ( abs(driveTrain->getLeftEncoder()) >= 100) {
    return true;
  }
}

void LogPositionCommand::finish() {
  fclose(logFile);
  driveTrain->stop();
}
