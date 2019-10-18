#ifndef INTAKECOMMAND_H_
#define INTAKECOMMAND_H_
#include "../main.h"
#include "Command.h"
#include "TraySubsystem.h"
/**
 * Base class for autonomous actions.
 * All funtions of this class must be implemented in child classes
 *
 */
class IntakeCommand : public Command {
public:

    IntakeCommand(std::shared_ptr<TraySubsystem> tray, double intakeSpeed, double timeout);

    void start();
    void update();
    bool isFinished();
  void finish();

private:
    std::shared_ptr<TraySubsystem> tray;

    double intakeSpeed, timeout;
};

#endif /* INTAKECOMMAND_H_ */
