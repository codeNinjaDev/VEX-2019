#ifndef INCHENCODER_H_
#define INCHENCODER_H_
#include "../main.h"
#include <iostream>

class InchEncoder : public pros::ADIEncoder {
public:
	InchEncoder(std::uint8_t iportTop, std::uint8_t iportBottom, double wheelDiameter, bool ireversed = false);
  double getInches();
private:
	double wheelDiameter;

};

#endif
