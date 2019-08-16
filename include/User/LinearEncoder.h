#ifndef LINEARENCODER_H_
#define LINEARENCODER_H_
#include "../main.h"
#include <iostream>
/**
 * Encoder class that inherits ADIEncoder,
 */
class LinearEncoder : public pros::ADIEncoder {
public:
	/**
	 * @param iportTop      Top port for Encoder
	 * @param iportBottom   Bottom port for ENCODER
	 * @param gear ratio gear ratio
	 * @param ireversed     Reverse direction?
	 */
	LinearEncoder(std::uint8_t iportTop, std::uint8_t iportBottom, double gearRatio, bool ireversed = false);
	/**
	 * Gets height from encoder
	 * @returns Get the height in inches
	 */
	double getHeight();
private:
	double gearRatio;

};

#endif
