#ifndef __INPUTTER_OUTPUTTER_H__
#define __INPUTTER_OUTPUTTER_H__

#include <vector>

class InputterOutputter
{
protected:
    std::vector<long> m_values;
    int m_get_position;
    int size();
public:
    InputterOutputter();
    ~InputterOutputter();
    void add(long value);
    void add(std::vector<long> values);
    int getNext(long * result);
    int getPosition(int position, long * result);
    int replace(long value, int position);
    bool hasAvailableElements();
};

#endif
