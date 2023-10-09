#pragma once

class CharacterSetHelper
{
private:
    static unsigned char asciiCharacterSet[256];

public:
    static void ConvertEBCDICToASCII(unsigned char* ebcdicString);
};