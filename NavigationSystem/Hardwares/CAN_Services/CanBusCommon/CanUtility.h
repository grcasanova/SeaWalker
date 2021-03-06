/****************************************************************************************
 *
 * File:
 *    CanUtility.h
 *
 * Purpose:
 *
 * Developer Notes:
 *    Created by dkarlsso on 2018-04-12
 *
 ***************************************************************************************/

#ifndef SAILINGROBOT_UTILITY_H
#define SAILINGROBOT_UTILITY_H

#include <stdint.h>

class CanUtility {
   public:
    /*
     * To map
     * [A, B] --> [a, b]
     *
     * use this formula
     * (val - A)*(b-a)/(B-A) + a
     *
     * Note: This function has to be kept identical to the corresponding
     * Arduino-function (also, it has no bracketing but is essentially a linear
     * projection)
     */
    static float mapInterval(float val, float fromMin, float fromMax, float toMin, float toMax);

    /**
     * Calculates maxvalue of a no of bytes.
     *
     * Eg. 1 byte --> 256 and so on
     *
     * @param noOfBytes
     * @return The maximum value of the given no of bytes
     */
    static uint64_t calcSizeOfBytes(int noOfBytes);
};

#endif  // SAILINGROBOT_UTILITY_H
