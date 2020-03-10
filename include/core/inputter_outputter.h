#ifndef __INPUTTER_OUTPUTTER_H__
#define __INPUTTER_OUTPUTTER_H__

#include <vector>

class InputterOutputter
{
private:
    std::vector<int> m_values;
    int m_get_position;
    int size();
public:
    InputterOutputter();
    ~InputterOutputter();
    void add(int value);
    void add(std::vector<int> values);
    int getNext(int * result);
    int getPosition(int position, int * result);
    int replace(int value, int position);
    bool hasAvailableElements();
};

#endif
