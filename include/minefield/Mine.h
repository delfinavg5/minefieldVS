#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "DataModel.h"
#include "Board.h"
#include "Player.h"
#include "Minefield.h"
namespace GameMine
{
    int configureMines();
    void getCoordinates(int numberOfMines, std::vector<dataModel::Cell> &mines, dataModel::Board &board);
    bool checkMinePosition(dataModel::Cell const &mine1, dataModel::Cell const &mine2);
    void cancelMine(dataModel::Board &board, dataModel::Player &player, dataModel::Cell const &mineToErase);
}