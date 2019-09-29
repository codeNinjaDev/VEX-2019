#include "user/logpositioncommand.h"
#include <cmath>
#include <math.h>

LogPositionCommand::LogPositionCommand(std::shared_ptr<DriveSubsystem> drive, double timeout) : driveTrain(drive)
{
  this->goalTime = timeout;
  // create csv file to write to
  logFile = fopen("/usd/position.csv", "w");
  // Make the header
  fprintf(logFile, "%s,%s\n", "Position (Inches)", "Time (seconds)");
  currentPosition = 0;
  std::printf("%s\n", "Log Constructor");
}

void LogPositionCommand::start() {
  // set the start time to the current timestamp
  startTime = timer.millis().getValue() / 1000;
  driveTrain->reset();
  std::printf("Start Time is %f\n", startTime);

}

void LogPositionCommand::update() {
  // Spin the robot full speed

  driveTrain->arcadeDrive(0, .1, false);

  currentPosition = driveTrain->getLeftEncoder();

  double currentTime = (timer.millis().getValue() / 1000) - startTime;
  std::printf("Curr Time %3f\n", currentTime);

  // Log the current position and current time
  fprintf(logFile, "%f,%f\n", currentPosition, currentTime);


}

bool LogPositionCommand::isFinished() {

  // Check if the timeout (if it has reached it's time limit) is completed
  double currentTime = timer.millis().getValue() / 1000;
  std::printf("Time elapsed: %f, Goal Time: %f, Distance: %f\n", currentTime - startTime, goalTime, driveTrain->getLeftEncoder());

  if (currentTime - startTime >= goalTime) {
    return true;
  }
  // Spin until 100 in
  if ( abs(driveTrain->getLeftEncoder()) >= 100) {
    return true;
  }
  return false;
}

void LogPositionCommand::finish() {
  // Close the file
  fclose(logFile);
  // Stop driving
  std::printf("%s\n", "Log FInish");
  driveTrain->stop();
}
