#include <iostream>
#include <string>

#include "segment_display.h"

SegmentDisplay::SegmentDisplay(std::string name, int value)
{
    m_name=name;
    m_value=value;
}

SegmentDisplay::~SegmentDisplay()
{
}

std::string SegmentDisplay::getName()
{
    return m_name;
}

int SegmentDisplay::getValue()
{
    return m_value;
}

void SegmentDisplay::setValue(int value)
{
    m_value=value;
}

void SegmentDisplay::display(std::ostream & out)
{
    out << m_name << ": " << m_value << std::endl;
}
