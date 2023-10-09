#include "IBMFloatingPointParser.h"
#include "Endian.h"

float IBMFloatingPointParser::ParseAsIEEEFloatingPoint(unsigned int ibmFloatingPoint)
{
    int sign{};
    int exponent{};
    unsigned int fraction{ ibmFloatingPoint };
    
    // Extract 32nd Bit for Sign.
    sign = static_cast<int>(fraction >> 31);

    // Remove Sign from Fraction.
    fraction <<= 1;

    // Extract 7 Bits from Fraction.
    exponent = static_cast<int>(fraction >> 25);

    // Remove Exponent from Fraction.
    fraction <<= 7;

    // Hard Zero
    if (fraction == 0)
    {
        exponent = 0;
    }
    else
    {
        /*  Adjust Exponent
            From: [Base 16 offset 64 radix point before first digit] == [16^(exponent - 64)] 
            To: [Base 2 offset 127 radix point after first digit] == [2^(exponent - 127)] */
        //  = (exponent - 64) * 4 + 127 - 1
        //  = (exponent * 4) - 256 + 126
        //  = (exponent * 2^2) - 130
        //  = (exponent << 2) - 130
        exponent = (exponent << 2) - 130;
    
        // Renormalize Fraction.
        while (fraction < 0x80000000)
        {
            // 3 times max for normalized input.
            --exponent;
            fraction <<= 1; // fraction * 2
        }

        // Exponent Underflow
        if (exponent <= 0)
        {
            // If exponent is complete underflow.
            if (exponent < -24)
            {
                fraction = 0;
            }  
            else // If exponent if partially underflow, denormalize fraction.
            {
                // fraction * (2 ^ -(-exponent)) == fraction * (2 ^ exponent)
                fraction >>= -exponent; 
            }

            exponent = 0;
        }
        else if (exponent >= 255) // Exponent Overflow
        {
            fraction = 0;
            exponent = 255;
        }
        else // Remove the assumed high bit from the fraction.
        {
            fraction <<= 1; // fraction * 2
        }
    }

    // Restore 24 Bits for Fraction.
    fraction >>= 8;

    // Create IEEE Floating Point Number.
    unsigned int ieeeFloatingPoint = 
        static_cast<unsigned int>(sign << 31) |
        static_cast<unsigned int>(exponent << 23) |
        (fraction >> 1);

    return *(reinterpret_cast<float*>(&ieeeFloatingPoint)); 
}