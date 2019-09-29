#include "user/PIDController.h"
#include "math.h"
using namespace std;

PIDController::PIDController(double P, double I, double D, double maxRange, double percentTolerance, bool stopOnTarget) {
  this->P = P;
  this->I = I;
  this->D = D;
  this->maxRange = maxRange;
  this->percentTolerance = percentTolerance;
  this->stopOnTarget = stopOnTarget;

  this->summation = 0;
  this->feedback = 0;
  this->setpoint = 0;
  this->aff = 0;
}

void PIDController::setSetpoint(double setpoint) {
  this->setpoint = setpoint;
}

double PIDController::run(double input) {
  this->feedback = input;
  currentError = setpoint - feedback;
  summation += currentError * I;
  deltaError = currentError - lastError;
  output = P * currentError + I * summation + D * deltaError;
  lastError = currentError;
  output += aff;
  if(output > maxRange)
      output = maxRange;
  else if(output < -maxRange)
      output = -maxRange;

  if(onTarget() && stopOnTarget) {
    output = 0;
  }
  return output;
}

void PIDController::setArbitraryFF(double ff) {
  aff = ff;
}

bool PIDController::onTarget() {
  currentError = setpoint -feedback;
  double percent = percentTolerance * .01;
  if(abs(currentError) < setpoint*percent)
      return true;
  else
      return false;

}
