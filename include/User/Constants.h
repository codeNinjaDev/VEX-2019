#ifndef CONSTANTS_H
#define CONSTANTS_H


const int FRONT_LEFT_MOTOR_PORT = 3;
const int FRONT_RIGHT_MOTOR_PORT = 2;
const int BACK_LEFT_MOTOR_PORT = 4;
const int BACK_RIGHT_MOTOR_PORT = 1;

const int LEFT_TOP_ENCODER_PORT = 6;
const int LEFT_BOTTOM_ENCODER_PORT = 7;

const int RIGHT_TOP_ENCODER_PORT = 0;
const int RIGHT_BOTTOM_ENCODER_PORT = 1;

const bool ARCADE_DRIVE = false;

const double BACK_WHEEL_DIAMETER = 4;
const double FRONT_WHEEL_DIAMETER = 3.25;

const double TRACK_WIDTH = 11.25;

const int DO_NOTHING_AUTO = 0;
const int LOG_POS_AUTO = 1;
const int LOG_VEL_AUTO = 2;


//NOT TECHNICALLY A CONSTANT
extern int SELECTED_AUTO_NUMBER = 0;
#endif
