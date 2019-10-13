#ifndef CONSTANTS_H
#define CONSTANTS_H

// Drive MOTOR PORTS

const int FRONT_LEFT_MOTOR_PORT = 1;
const int FRONT_RIGHT_MOTOR_PORT = 10;
const int BACK_LEFT_MOTOR_PORT = 14;
const int BACK_RIGHT_MOTOR_PORT = 20;

const int TRAY_MOTOR_PORT =  11;

const int LEFT_INTAKE_MOTOR_PORT = 15;
const int RIGHT_INTAKE_MOTOR_PORT = 18;

const int ARM_MOTOR_PORT = 19;

const double ROBOT_LENGTH = 15.5;
const int LIMIT_SWITCH_PORT = 'A';

// ROBOT CONSTANTS

const double BACK_WHEEL_DIAMETER = 4;

/**
 * Horizontal distance between center of left
 * side wheels and center of right side wheels
 *
 *
 * Distance between center of front left wheel and center of back left wheel
 */
const double WHEELBASE_WIDTH = 10;

// PARAMETERS

const bool ARCADE_DRIVE = true;

// AUTONOMOUS ROUTINES

const int DO_NOTHING_AUTO = 0;
const int DRIVE_FORWARD_AUTO = 1;
const int SMALL_RED = 2;
const int SMALL_BLUE = 2;


// LIFT SETPOINTS
const double HOME = 0;
// GAME PIECE Constants
const double HEIGHT_OF_CUBE = 5.5;
const double HEIGHT_OF_TOWER = 18;

#endif
