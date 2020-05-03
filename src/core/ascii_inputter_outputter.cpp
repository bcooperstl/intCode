#include <iostream>
#include <vector>
#include <string>

#include "ascii_inputter_outputter.h"
#include "constants.h"

AsciiInputterOutputter::AsciiInputterOutputter():InputterOutputter()
{
}

AsciiInputterOutputter::~AsciiInputterOutputter()
{
    m_values.clear();
}

void AsciiInputterOutputter::add(std::string str)
{
    for (int i=0; i<str.length(); i++)
        m_values.push_back(str[i]);
}

void AsciiInputterOutputter::add(char ch)
{
    m_values.push_back(ch);
}

void AsciiInputterOutputter::addNewline()
{
    m_values.push_back(NEWLINE);
}

int AsciiInputterOutputter::getNextChar(char * ch)
{
    if (m_get_position >= size())
    {
        std::cerr << "Attempted to read position " << m_get_position << " in a " << size() << " length vector" << std::endl;
        return ERR_NO_ELEMENT;
    }
    if (!hasAvailableAscii())
    {
        std::cerr << "Attempted to read ASCII at position " << m_get_position << " but it is not ASCII" << std::endl;
        return ERR_NO_ASCII;
    }
    *ch = m_values[m_get_position++];
    return SUCCESS;
}

int AsciiInputterOutputter::getNextString(std::string & str)
{
    if (m_get_position >= size())
    {
        std::cerr << "Attempted to read position " << m_get_position << " in a " << size() << " length vector" << std::endl;
        return ERR_NO_ELEMENT;
    }
    if (!hasAvailableAscii())
    {
        std::cerr << "Attempted to read ASCII at position " << m_get_position << " but it is not ASCII" << std::endl;
        return ERR_NO_ASCII;
    }
    str.clear();
    while (hasAvailableAscii())
    {
        str=str+((char)m_values[m_get_position++]);
    }
    return SUCCESS;
}

int AsciiInputterOutputter::getPositionChar(int position, char * result)
{
    if ((position < 0) || (position >= size()))
    {
        std::cerr << "Attempted to read position " << position << " in a " << size() << " length vector" << std::endl;
        return ERR_NO_ELEMENT;
    }
    if (m_values[position]>=0 && m_values[position]<=255)
    {
        std::cerr << "Attempted to read ASCII at position " << m_get_position << " but it is not ASCII" << std::endl;
        return ERR_NO_ASCII;
    }
    *result = m_values[position];
    return SUCCESS;
}

bool AsciiInputterOutputter::hasAvailableAscii()
{
    return ((m_get_position < size()) && (m_values[m_get_position] >= 0 && m_values[m_get_position] <= 255));
}
