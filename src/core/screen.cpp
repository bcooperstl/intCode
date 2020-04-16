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
#ifdef DEBUG_SCREEN
    std::cerr << "Setting rows to " << num_rows << std::endl;
#endif
    m_rows = num_rows;
    m_tiles.resize(num_rows);
    setCols(m_cols);
#ifdef DEBUG_SCREEN
    std::cerr << "Done setting rows" << std::endl;
#endif
}

void Screen::setCols(int num_cols)
{
#ifdef DEBUG_SCREEN
    std::cerr << "Setting cols to " << num_cols << std::endl;
#endif
    m_cols = num_cols;
    for (int i=0; i<m_rows; i++)
    {
        m_tiles[i].resize(num_cols);
    }
#ifdef DEBUG_SCREEN
    std::cerr << "Done setting cols" << std::endl;
#endif
}

void Screen::set(int row, int col, Tile tile)
{
#ifdef DEBUG_SCREEN
    std::cerr << "Settings " << row << "," << col << " to " << tile.getValue() << " with size " << m_rows << "," << m_cols << std::endl;
#endif
    if (row >= m_rows)
    {
#ifdef DEBUG_SCREEN
        std::cerr << "need to increment rows" << std::endl;
#endif
        setRows(row+1);
    }
    if (col >= m_cols)
    {
#ifdef DEBUG_SCREEN
        std::cerr << "Need to increment cols" << std::endl;
#endif
        setCols(col+1);
    }
    m_tiles[row][col]=tile;
}

void Screen::clear(int row, int col)
{
    Tile t;
    if (row >= m_rows)
        setRows(row+1);
    if (col >= m_cols)
        setCols(col+1);
    m_tiles[row][col]=t;
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
    *tile=&m_tiles[row][col];
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
