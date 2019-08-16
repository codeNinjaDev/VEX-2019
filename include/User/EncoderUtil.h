#ifndef ENCODERUTIL_H_
#define ENCODERUTIL_H_
#include "../main.h"
#include <iostream>
/**
 * Class that helps with Encoder math
 */
class EncoderUtil {
public:
	/**
	 * Gets ticks from encoder
	 * @param ticks The current number of ticks of ENCODER
	 * @param wheelDiameter Diameter of wheel
	 * @returns Get the distance in inches
	 */
	static double getInches(int ticks, double wheelDiameter);


};

#endif
