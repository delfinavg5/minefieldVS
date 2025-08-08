#pragma once
#include <vector>

namespace dataModel
{
    struct Cell
    {
        unsigned int row = 0;
        unsigned int column = 0;
    };
    struct Player
    {
        int id;
        std::vector<dataModel::Cell> mines;
        std::vector<dataModel::Cell> guesses;
        int remainingMines;
    };
    struct Board
    {
        std::vector<std::vector<char>> matrix;
    };
}