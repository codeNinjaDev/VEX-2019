#ifndef CONSTANTS_H
#define CONSTANTS_H

// Drive MOTOR PORTS

const int FRONT_LEFT_MOTOR_PORT = 1;
const int FRONT_RIGHT_MOTOR_PORT = 10;
const int BACK_LEFT_MOTOR_PORT = 14;
const int BACK_RIGHT_MOTOR_PORT = 20;

const int TRAY_MOTOR_PORT =  11;

const int LEFT_INTAKE_MOTOR_PORT = 13;
const int RIGHT_INTAKE_MOTOR_PORT = 18;

const int ARM_MOTOR_PORT = 19;


const int LIMIT_SWITCH_PORT = 'A';

// ROBOT CONSTANTS

const double BACK_WHEEL_DIAMETER = 4;
const double FRONT_WHEEL_DIAMETER = 3.25;
/**
 * Horizontal distance between center of left
 * side wheels and center of right side wheels
 *
 * OR
 *
 * Distance between center of front left wheel and center of back left wheel
 */
const double TRACK_WIDTH = 11.25;

// PARAMETERS

const bool ARCADE_DRIVE = true;

// AUTONOMOUS ROUTINES

const int DO_NOTHING_AUTO = 0;
const int DRIVE_FORWARD_AUTO = 1;
const int LOG_VEL_AUTO = 2;
const int HOME_LIFT_AUTO = 3;
const int SCORE_SINGLE_CUBE_AUTO = 4;

// LIFT SETPOINTS
const double HOME = 0;
static double LIFT_TOP_HEIGHT = 40;
// GAME PIECE Constants
const double HEIGHT_OF_CUBE = 6;
const double HEIGHT_OF_TOWER = 18;

#endif
