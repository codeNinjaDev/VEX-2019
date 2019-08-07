#ifndef CONSTANTS_H
#define CONSTANTS_H

// MOTOR PORTS

const int FRONT_LEFT_MOTOR_PORT = 3;
const int FRONT_RIGHT_MOTOR_PORT = 2;
const int BACK_LEFT_MOTOR_PORT = 4;
const int BACK_RIGHT_MOTOR_PORT = 1;

// ENCODER PORTS

const int LEFT_TOP_ENCODER_PORT = 6;
const int LEFT_BOTTOM_ENCODER_PORT = 7;

const int RIGHT_TOP_ENCODER_PORT = 0;
const int RIGHT_BOTTOM_ENCODER_PORT = 1;

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

#endif
