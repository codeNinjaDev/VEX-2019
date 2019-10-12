## Initialize Function

This initializes the susbsystems, resets the sensors, and list the autonomous options on the V5 Screen.

```
void initialize() {
  drive.reset(new DriveSubsystem(driver));
  tray.reset(new TraySubsystem(driver, operatorController));
  autoSelector.registerAuto("DRIVE FORWARD AUTO", DRIVE_FORWARD_AUTO);
  autoSelector.registerAuto("SMALL RED ZONE", SMALL_RED);
  autoSelector.registerAuto("SMALL BLUE ZONE", SMALL_BLUE);
  autoSelector.listOptions();
}
```

## OpControl Function

This runs in a loop and calls the subsystems' update function

```
void opcontrol() {
 	while (true) {
 		std::printf("Running");
 		drive->update();
    tray->update();
 		pros::delay(20);
 	}
  tray->stop();
 	drive->stop();
 }

```

## Subsystems
This is the base class for subsystems. All Subsystems must implement this class.

```
class Subsystem {
public:

	/**
	 * Abstract function that configures sensors and motors or anything else that needs
	 * to be done before the robot runs.
	 */
	virtual void initialize() = 0;
	/**
	 * Looped function to run subsystem motors
	 */
  virtual void update() = 0;
	/**
	 * Function to reset subsystems sensors, etc...
	 */
  virtual void reset() = 0;
	/**
	 * Function to stop subsystem operations such as setting motors to zero
	 */
	virtual void stop() = 0;
};
```


## Commands
Autonomous actions that use subsystems. It allows complex behavior while keeping the code readable and sequential.
All commands must implement this class:

```
class Command {
public:

	/**
	 * Abstract function that is called before the while loop only once. Common use case is to setup the command.
	 */
	virtual void start() = 0;
	/**
	 * Abstract function that is run in a while loop until *isFinished()* returns true and contains the meat of the command, such as running motors.
	 */
  virtual void update() = 0;
	/**
	 * Abstract function that runs in a while loop and continously checks if the command should end. If true, ends while loop.
	 * Common use case is to check if timeout for command is exceeded
	 * @return True if command should end, false if it should not.
	 */
  virtual bool isFinished() = 0;
	/**
	 * Abstract function that runs after the while loop and only once.
	 * Normally wraps up a command and gets the robot ready to transition to a new command.
	 */
	virtual void finish() = 0;

	// These variables are to ensure that there is a time limit allotted for each command and that no command
	// exceeds the limit (also called a timeout)

	/**
	 * Variable to store the starting timestamp of the command.
	 */
	double startTime;
	/**
	 * Variable to store the maximum allowed time for a command to run.
	 */
	double goalTime;
	okapi::Timer timer;

};
```
