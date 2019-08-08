#include "user/inchencoder.h"
#include <math.h>

InchEncoder::InchEncoder(std::uint8_t iportTop, std::uint8_t iportBottom, double wheelDiameter, bool ireversed)
  : pros::ADIEncoder (iportTop, iportBottom, ireversed)
{
  this->wheelDiameter = wheelDiameter;
}

double InchEncoder::getInches() {
  // 2pi*r = circumference
  // circumference = 1 revolution traveled = 360 ticks
  // Distance traveled = 2pi*r*get_value / 360
  return (M_PI * wheelDiameter * pros::ADIEncoder::get_value()) / 360;
}
