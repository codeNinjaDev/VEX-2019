#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "../main.h"

// Drive MOTOR PORTS

const int FRONT_LEFT_MOTOR_PORT = 1;
const int FRONT_RIGHT_MOTOR_PORT = 10;
const int BACK_LEFT_MOTOR_PORT = 16;
const int BACK_RIGHT_MOTOR_PORT = 20;

const int TRAY_MOTOR_PORT = 11;

const int LEFT_INTAKE_MOTOR_PORT = 14;
const int RIGHT_INTAKE_MOTOR_PORT = 19;

const int ARM_MOTOR_PORT = 9;

const okapi::QLength ROBOT_LENGTH = 15.5_in;
const int LIMIT_SWITCH_PORT = 'A';

// ROBOT CONSTANTS

const okapi::QLength BACK_WHEEL_DIAMETER = 4_in;

/**
 * Horizontal distance between center of left
 * side wheels and center of right side wheels
 *
 *
 */
const okapi::QLength WHEELBASE_WIDTH = 10_in;

// PARAMETERS

const bool ARCADE_DRIVE = true;

// AUTONOMOUS ROUTINES

const int DO_NOTHING_AUTO = 0;
const int SMALL_RED = 1;
const int SMALL_BLUE = 2;
const int LARGE_RED = 3;
const int LARGE_BLUE = 4;
const int SKILLS_RUN = 5;
const int DRIVE_FORWARD_AUTO = 6;
const int ONE_CUBE_AUTO = 7;
const int SMALL_RED_MANUAL = 8;




// LIFT SETPOINTS
const double HOME = 0;
// GAME PIECE Constants
const okapi::QLength HEIGHT_OF_CUBE = 5.5_in;
const okapi::QLength HEIGHT_OF_TOWER = 18_in;

#endif
