#include "user/encoderutil.h"
#include <math.h>

double EncoderUtil::getInches(int ticks, double wheelDiameter) {
  // 2pi*r = circumference
  // circumference = 1 revolution traveled = 360 ticks
  // Distance traveled = 2pi*r*get_value / 360
  return (M_PI * wheelDiameter * ticks) / 360;
}
