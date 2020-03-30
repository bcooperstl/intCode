#ifndef __SEGMENT_DISPLAY_H__
#define __SEGMENT_DISPLAY_H__

#include <iostream>
#include <string>

class SegmentDisplay
{
private:
    std::string m_name;
    int m_value;
public:
    SegmentDisplay(std::string name, int value);
    ~SegmentDisplay();
    std::string getName();
    int getValue();
    void setValue(int value);
    void display(std::ostream & out);
};

#endif
