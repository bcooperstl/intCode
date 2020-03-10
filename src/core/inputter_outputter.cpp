#include <iostream>
#include <vector>

#include "constants.h"
#include "inputter_outputter.h"

InputterOutputter::InputterOutputter()
{
    m_values.clear();
    m_get_position=0;
}

InputterOutputter::~InputterOutputter()
{
    m_values.clear();
}

int InputterOutputter::size()
{
    return m_values.size();
}

void InputterOutputter::add(int value)
{
    m_values.push_back(value);
}

void InputterOutputter::add(std::vector<int> values)
{
    for (int i=0; i<values.size(); i++)
        m_values.push_back(values[i]);
}

int InputterOutputter::getNext(int * result)
{
    if (m_get_position >= size())
    {
        std::cerr << "Attempted to read position " << m_get_position << " in a " << size() << " length vector" << std::endl;
        return ERR_NO_ELEMENT;
    }
    *result = m_values[m_get_position++];
    return SUCCESS;
}

int InputterOutputter::getPosition(int position, int * result)
{
    if ((position < 0) || (position >= size()))
    {
        std::cerr << "Attempted to read position " << position << " in a " << size() << " length vector" << std::endl;
        return ERR_NO_ELEMENT;
    }
    *result = m_values[position];
    return SUCCESS;
}

int InputterOutputter::replace(int value, int position)
{
    if ((position < 0) || (position >= size()))
    {
        std::cerr << "Attempted to replace position " << position << " in a " << size() << " length vector" << std::endl;
        return ERR_NO_ELEMENT;
    }
    m_values[position]=value;
    return SUCCESS;
}

bool InputterOutputter::hasAvailableElements()
{
    return (m_get_position < size());
}
