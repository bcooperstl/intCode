#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "program_runner.h"

Runner::Runner(std::string name)
{
    init(name);
}

Runner::Runner()
{
    std::stringstream nameStream;
    nameStream << "noName" << this;
    init(nameStream.str());
}

void Runner::init(std::string name)
{
    m_terminated = false;
    m_service = false;
    m_name = name;
}

Runner::~Runner()
{
}

bool Runner::isTerminated()
{
    return m_terminated;
}

bool Runner::isService()
{
    return m_service;
}

void Runner::setService(bool service)
{
    m_service = service;
}

std::string Runner::getName()
{
    return m_name;
}
