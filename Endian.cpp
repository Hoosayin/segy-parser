#include "Endian.h"

Endian* Endian::m_instance{ nullptr };

Endian::Endian()
{
    // Set Machine Endian.
    int number{1};
    char *bytes{reinterpret_cast<char *>(&number)};

    m_machineEndian = *bytes ? ENDIAN_TYPE::LITTLE : ENDIAN_TYPE::BIG;   
}

Endian::~Endian()
{
    // Clean up.
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Endian *Endian::GetInstance()
{
    if (!m_instance)
        m_instance = new Endian();
    
    return m_instance;
}

void Endian::FlipBytes(
    char *bytes, 
    const size_t& size, 
    const ENDIAN_TYPE& streamEndian)
{
    /* Return for a single byte,
       or stream endian is already in machine endian. */
    if (size < 2 ||
        m_machineEndian == streamEndian)
        return;

    /* Start swapping first byte with the last one,
       until starting point and ending point reaches the mid point. */
    char *start = &bytes[0];
    char *end = &bytes[size - 1];

    while (start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;

        ++start;
        --end;
    }
}
