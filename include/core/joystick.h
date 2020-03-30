#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

enum JoystickPosition {left=-1, neutral=0, right=1};

class Joystick
{
private:
    JoystickPosition m_position;
    int m_cols;
public:
    Joystick();
    ~Joystick();
    void setPosition(JoystickPosition position);
    JoystickPosition getPosition();
};

#endif
