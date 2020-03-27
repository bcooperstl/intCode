#ifndef __TILE_H__
#define __TILE_H__

#define BLANK_TILE ' '

class Tile
{
private:
    char m_value;
public:
    Tile();
    Tile(char value);
    Tile(const Tile & other);
    ~Tile();
    char getValue();
};

#endif
