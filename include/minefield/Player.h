#pragma once
#include <iostream>
#include <vector>

#include "DataModel.h"
#include "Minefield.h"


int getInputInRange(const std::string &prompt, int min, int max);

namespace GamePlayer
{
    void setupPlayers(std::vector<dataModel::Player> &players, int minesAmount);
    int numberOfMinesToGuess(dataModel::Board &board, dataModel::Player &actual, std::vector<dataModel::Player> &players);
    void resizeVectors(dataModel::Board &board, std::vector<dataModel::Player> &players);
    const dataModel::Player *getWinner(const std::vector<dataModel::Player> &players);
}