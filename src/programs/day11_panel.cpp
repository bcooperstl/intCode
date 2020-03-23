#include "day11_panel.h"

Panel::Panel(PanelColor color)
{
    m_color=color;
    m_painted=false;
}

Panel::~Panel()
{
}

PanelColor Panel::getColor()
{
    return m_color;
}

bool Panel::isPainted()
{
    return m_painted;
}

void Panel::paint(PanelColor new_color)
{
    m_painted=true;
    m_color=new_color;
}

PanelOutput Panel::getOutput()
{
    if (m_color==black)
        return outputBlack;
    else if (m_color==white)
        return outputWhite;
    return outputBlack;
}

void Panel::setStatus(PanelColor color, bool painted)
{
    m_color=color;
    m_painted=painted;
}

