#include <iostream>
#include <cstring>
#include <sstream>
#include <string>

#include "constants.h"
#include "day25_part1_runner.h"
#include "runner.h"
#include "ascii_inputter_outputter.h"

#define QUIT "QUIT"
#define STEPS_TO_DOOR 32

Day25Part1Runner::Day25Part1Runner(std::string name, AsciiInputterOutputter * fromIntcode, AsciiInputterOutputter * toIntcode):Runner(name)
{
    m_from_intcode=fromIntcode;
    m_to_intcode=toIntcode;
    m_programs[0]="south";
    m_programs[1]="east";
    m_programs[2]="take whirled peas";
    m_programs[3]="west";
    m_programs[4]="north";
    m_programs[5]="north";
    m_programs[6]="east";
    m_programs[7]="take ornament";
    m_programs[8]="north";
    m_programs[9]="north";
    m_programs[10]="take dark matter";
    m_programs[11]="south";
    m_programs[12]="south";
    m_programs[13]="west";
    m_programs[14]="west";
    m_programs[15]="west";
    m_programs[16]="take candy cane";
    m_programs[17]="west";
    m_programs[18]="west";
    m_programs[19]="take tambourine";
    m_programs[20]="east";
    m_programs[21]="east";
    m_programs[22]="east";
    m_programs[23]="north";
    m_programs[24]="take astrolabe";
    m_programs[25]="east";
    m_programs[26]="take hologram";
    m_programs[27]="east";
    m_programs[28]="take klein bottle";
    m_programs[29]="west";
    m_programs[30]="south";
    m_programs[31]="west";
    
    m_program_steps=0;
    
    m_items[0]="whirled peas";
    m_items[1]="ornament";
    m_items[2]="dark matter";
    m_items[3]="candy cane";
    m_items[4]="tambourine";
    m_items[5]="astrolabe";
    m_items[6]="hologram";
    m_items[7]="klein bottle";
    
    m_permutation=-1;
    m_found_it=false;
}

Day25Part1Runner::~Day25Part1Runner()
{
}

int Day25Part1Runner::run()
{
    std::string asciiOut, asciiIn;
    long value;
    int rc;

    
    if (m_from_intcode->hasAvailableAscii())
    {
        rc = m_from_intcode->getNextString(asciiOut);
        if (rc != SUCCESS)
        {
            std::cerr << "Error getting ASCII output" << std::endl;
            return rc;
        }
        std::cout << asciiOut;
    }
    if (m_permutation>0)
    {
        if (asciiOut.find("Droids on this ship are heavier than the detected value")==std::string::npos &&
            asciiOut.find("Droids on this ship are lighter than the detected value")==std::string::npos)
        {
            found_it=true;
        }
    }

    if (m_program_steps < STEPS_TO_DOOR)
    {
        m_to_intcode->add(m_program_steps[i]);
        m_to_intcode->addNewline();
    }
    else if (m_permutation==-1)
    {
        for (int i=0; i<8; i++) // drop all items at the security checkpoint
        m_to_intcode->add("drop ");
        m_to_intcode->add(m_items[i]);
        m_to_intcode->addNewline();
        m_permutation=0;
    }
    else if (!found_it)
    {
        // drop what we have and pick up new items
        for (int i=0; i<8; i++)
        {
            if (m_permutation&(1<<i))
            {
                m_to_intcode->add("drop ");
                m_to_intcode->add(m_items[i]);
                m_to_intcode->addNewline();
            }
        }
        m_permutation++;
        for (int i=0; i<8; i++)
        {
            if (m_permutation&(1<<i))
            {
                m_to_intcode->add("take ");
                m_to_intcode->add(m_items[i]);
                m_to_intcode->addNewline();
            }
        }
        m_to_intcode->add("north");
        m_to_intcode->addNewline();
    }
    else
    {
        std::cout << " >";
        getline(std::cin,asciiIn);
    }
        
    if (asciiIn==QUIT)
    {
        m_terminated=true;
        return SUCCESS;
    }
    
    m_to_intcode->add(asciiIn);
    m_to_intcode->addNewline();
    return INPUT_WAIT;
}
