#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>
#include <iostream>

#include "tile.h"

class Screen
{
private:
    std::vector<std::vector<Tile>> m_tiles;
    int m_rows;
    int m_cols;
    void setRows(int num_rows);
    void setCols(int num_cols);
public:
    Screen();
    Screen(int num_rows, int num_cols);
    ~Screen();
    void set(int row, int col, Tile tile);
    void clear(int row, int col);
    void display(std::ostream & out);
    int getNumRows();
    int getNumCols();
    int getTile(int row, int col, Tile ** tile);
};

#endif
