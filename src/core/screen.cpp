#include <iostream>
#include <vector>

#include "constants.h"
#include "tile.h"
#include "screen.h"

Screen::Screen()
{
    m_rows=0;
    m_cols=0;
    m_tiles.clear();
    m_tiles.resize(0);
}

Screen::Screen(int num_rows, int num_cols)
{
    setRows(num_rows);
    setCols(num_cols);
}

Screen::~Screen()
{
}

void Screen::setRows(int num_rows)
{
    m_rows = num_rows;
    m_tiles.resize(num_rows);
}

void Screen::setCols(int num_cols)
{
    m_cols = num_cols;
    for (int i=0; i<m_rows; i++)
    {
        m_tiles[i].resize(num_cols);
    }
}

void Screen::set(int row, int col, Tile tile)
{
    if (row > m_rows)
        setRows(row);
    if (col > m_cols)
        setCols(col);
    m_tiles[row-1][col-1]=tile;
}

void Screen::clear(int row, int col)
{
    Tile t;
    if (row > m_rows)
        setRows(row);
    if (col > m_cols)
        setCols(col);
    m_tiles[row-1][col-1]=t;
}

int Screen::getNumRows()
{
    return m_rows;
}

int Screen::getNumCols()
{
    return m_cols;
}

int Screen::getTile(int row, int col, Tile ** tile)
{
    if (row < 0 || row > m_rows)
        return ERR_OFF_SCREEN;
    if (col < 0 || col > m_cols)
        return ERR_OFF_SCREEN;
    *tile=&m_tiles[row-1][col-1];
    return SUCCESS;
}

void Screen::display(std::ostream & out)
{
    for (int i=0; i<m_rows; i++)
    {
        for (int j=0; j<m_cols; j++)
        {
            out << m_tiles[i][j].getValue();
        }
        out << std::endl;
    }
}
