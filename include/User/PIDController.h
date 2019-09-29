#ifndef PIDCONTROLLER_H_   /* Include guard */
#define PIDCONTROLLER_H_
class PIDController {

public:
  PIDController(double P, double I, double D, double maxRange, double percentTolerance, bool stopOnTarget);
  void setSetpoint(double setpoint);
  double run(double input);
  void setArbitraryFF(double ff);
  bool onTarget();

private:
  double deltaError, P, I, D, maxRange, percentTolerance, setpoint, summation, lastError, currentError, feedback, output, aff;
  bool stopOnTarget;
};
#endif // PIDCONTROLLER_H_
