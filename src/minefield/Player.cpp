#include "Player.h"

namespace GamePlayer{
    void setupPlayers(std::vector<dataModel::Player> &players, int minesAmount)
    {
        const int minPlayers = 0;
        const int maxPlayers = 4;
        int idCounter = 0;
        static const std::string prompt = "Enter how many players will participate\n";

        players.resize(GameMinefield::getInputInRange(prompt, minPlayers, maxPlayers));

        for (auto &player : players)
        {
            player.id = idCounter + 1;
            player.remainingMines = minesAmount;
            player.mines.resize(minesAmount);
            player.guesses.resize(minesAmount);
            idCounter++;
        }
    }

    int numberOfMinesToGuess(dataModel::Board &board, dataModel::Player &actual, std::vector<dataModel::Player> &players)
    {
        int minor = std::numeric_limits<int>::max();
        for (const auto &player : players)
        {
            if ((minor > player.remainingMines) && (player.id != actual.id))
            {
                minor = player.remainingMines;
            }
        }
        return minor;
    }
    
    void resizeVectors(dataModel::Board &board, std::vector<dataModel::Player> &players)
    {
        for (auto &player : players)
        {
            player.mines.resize(player.remainingMines);
            player.guesses.resize(numberOfMinesToGuess(board, player, players));
        }
    }

    const dataModel::Player *getWinner(const std::vector<dataModel::Player> &players)
    {
        if (players.empty())
        {
            return nullptr;
        }

        const dataModel::Player *winner = &players[0];
        for (const auto &player : players)
        {
            if (player.remainingMines != 0)
            {
                winner = &player;
            }
        }
        return winner;
    }
}