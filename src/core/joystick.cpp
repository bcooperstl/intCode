#include "joystick.h"

Joystick::Joystick()
{
    m_position=neutral;
}

Joystick::~Joystick()
{
}

void Joystick::setPosition(JoystickPosition position)
{
    m_position=position;
}

JoystickPosition Joystick::getPosition()
{
    return m_position;
}
