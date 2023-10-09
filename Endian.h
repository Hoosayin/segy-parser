#pragma once
#include <stddef.h>

enum class ENDIAN_TYPE
{
    BIG = 0,
    LITTLE = 1,
};

class Endian
{
private:
    static Endian* m_instance;
    ENDIAN_TYPE m_machineEndian{ ENDIAN_TYPE::LITTLE };

    Endian();

public:
    virtual ~Endian();
    static Endian* GetInstance();

    void FlipBytes(
        char* bytes, const size_t& size, 
        const ENDIAN_TYPE& streamEndian);
};