#include "tile.h"

Tile::Tile()
{
    m_value=BLANK_TILE;
}

Tile::Tile(char value)
{
    m_value=value;
}

Tile::Tile(const Tile & other)
{
    m_value=other.m_value;
}

Tile::~Tile()
{
}

char Tile::getValue()
{
    return m_value;
}
