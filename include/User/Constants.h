#ifndef CONSTANTS_H
#define CONSTANTS_H

// MOTOR PORTS

const int FRONT_LEFT_MOTOR_PORT = 3;
const int FRONT_RIGHT_MOTOR_PORT = 2;
const int BACK_LEFT_MOTOR_PORT = 4;
const int BACK_RIGHT_MOTOR_PORT = 1;

const int LEFT_LIFT_MOTOR_PORT = 5;
const int RIGHT_LIFT_MOTOR_PORT = 6;

const int INTAKE_MOTOR_PORT = 7;
const int CLAMP_MOTOR_PORT = 8;


const int LIGHT_SENSOR_PORT = 0;

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
const int LOG_POS_AUTO = 1;
const int LOG_VEL_AUTO = 2;
const int HOME_LIFT_AUTO = 3;

// LIFT SETPOINTS
const double HOME = 1;
const double LIFT_TOP_HEIGHT = 46;
// GAME PIECE Constants
const double HEIGHT_OF_CUBE = 6;
const double HEIGHT_OF_TOWER = 18;

#endif
