#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

#include "Minefield.h"
#include "OnlyCell.h"

namespace dataModel
{
    
}


namespace GameBoard
{
    bool validPosition(dataModel::Board &board, int row, int column);
    void printBoard(dataModel::Board const &board);
    void configureBoard(dataModel::Board &board);
}