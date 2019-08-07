#ifndef INCHENCODER_H_
#define INCHENCODER_H_
#include "../main.h"
#include <iostream>
/**
 * Encoder class that inherits ADIEncoder, but adds the functionality for distance inches given wheel diameter
 */
class InchEncoder : public pros::ADIEncoder {
public:
	/**
	 * @param iportTop      Top port for Encoder
	 * @param iportBottom   Bottom port for ENCODER
	 * @param wheelDiameter Wheel diamter in inches
	 * @param ireversed     Reverse direction?
	 */
	InchEncoder(std::uint8_t iportTop, std::uint8_t iportBottom, double wheelDiameter, bool ireversed = false);
	/**
	 * @returns Get the distance in inches
	 */
	double getInches();
private:
	double wheelDiameter;

};

#endif
