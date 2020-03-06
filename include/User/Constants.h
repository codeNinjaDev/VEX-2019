#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "../main.h"

// Drive MOTOR PORTS

const int FRONT_LEFT_MOTOR_PORT = 1;
const int FRONT_RIGHT_MOTOR_PORT = 10;
const int BACK_LEFT_MOTOR_PORT = 16;
const int BACK_RIGHT_MOTOR_PORT = 20;

const int TRAY_MOTOR_PORT = 11;

const int LEFT_INTAKE_MOTOR_PORT = 15;
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
const int IMU_PORT = 2;
const int DO_NOTHING_AUTO = 0;
const int ONE_CUBE_AUTO = 1;
const int LARGE_RED_3 = 2;
const int LARGE_BLUE_3 = 3;
const int TEST_DISTANCE = 4;
const int TEST_TURN = 5;
const int SMALL_RED_6 = 6;
const int SMALL_BLUE_6 = 7;
const int SMALL_RED_8 = 8;
const int SMALL_BLUE_8 = 9;
const int SKILLS = 10;
const int PREP_AUTO = 11;

// LIFT SETPOINTS
const double HOME = 0;
// GAME PIECE Constants
const okapi::QLength HEIGHT_OF_CUBE = 5.5_in;
const okapi::QLength HEIGHT_OF_TOWER = 18_in;

#endif
