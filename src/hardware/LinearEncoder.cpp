#include "user/linearencoder.h"
#include <math.h>
using namespace std;

LinearEncoder::LinearEncoder(std::uint8_t iportTop, std::uint8_t iportBottom, double gearRatio, bool ireversed)
  : pros::ADIEncoder (iportTop, iportBottom, ireversed)
{

}

double LinearEncoder::getHeight() {
  // 2pi*r = circumference
  // circumference = 1 revolution traveled = 360 ticks
  // Distance traveled = 2pi*r*get_value / 360
  //AsyncControllerFactory::posPID(1, ADIEncoder('A', 'B'), 0.001, 0.0, 0.0001);
  return (M_PI * gearRatio * pros::ADIEncoder::get_value()) / 360;
}
