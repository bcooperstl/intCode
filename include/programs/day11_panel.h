#ifndef __DAY_11_PANEL_H__
#define __DAY_11_PANEL_H__

enum PanelColor { black=0, white=1};
enum PanelOutput { outputBlack='.', outputWhite='#'};

class Panel
{
private:
    PanelColor m_color;
    bool m_painted;
public:
    Panel(PanelColor color=black);
    ~Panel();
    PanelColor getColor();
    bool isPainted();
    void paint(PanelColor newColor);
    PanelOutput getOutput();
    void setStatus(PanelColor color, bool painted);
};

#endif
