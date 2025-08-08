#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "DataModel.h"
#include "Board.h"
#include "Player.h"
#include "Mine.h"

namespace GameAction
{
    enum class ActionType
    {
        PlaceMines,
        MakeGuesses
    };

    struct Action
    {
        ActionType type = ActionType::PlaceMines;
        char const *string = "mines";
    };

    static constexpr GameAction::Action kActionPlaceMines{};
    static constexpr GameAction::Action kActionMakeGuesses{GameAction::ActionType::MakeGuesses, "guess"};
}

namespace GameMinefield
{
    void clearConsoleBuffer();
    int getInputInRange(const std::string &prompt, int min, int max);
    void handleAllPlayers(dataModel::Board &board, std::vector<dataModel::Player> &players, GameAction::Action const &action);
    void checkCollisions(dataModel::Board &board, std::vector<dataModel::Cell> const &coords, std::vector<dataModel::Player> &players);
    void checkMinesSameLocation(dataModel::Board &board, std::vector<dataModel::Player> &players);
    void checkGuesses(dataModel::Board &board, std::vector<dataModel::Player> &players);
    
    bool checkWinner(const std::vector<dataModel::Player> &players);
    void runMainLoop();
}