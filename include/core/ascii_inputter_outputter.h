#ifndef __ASCII_INPUTTER_OUTPUTTER_H__
#define __ASCII_INPUTTER_OUTPUTTER_H__

#include <vector>
#include <string>
#include "inputter_outputter.h"

#define NEWLINE '\n'

class AsciiInputterOutputter : public InputterOutputter
{
public:
    AsciiInputterOutputter();
    ~AsciiInputterOutputter();
    void add(std::string str);
    void add(char ch);
    void addNewline();
    int getNextChar(char * ch);
    int getNextString(std::string & str);
    int getPositionChar(int position, char * ch);
    bool hasAvailableAscii();
};

#endif
