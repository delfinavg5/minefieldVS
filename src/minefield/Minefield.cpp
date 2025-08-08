#include "Minefield.h"

namespace GameMinefield
{
    void clearConsoleBuffer()
    {
        static char const *const kClearConsoleBufferCommand = "cls";
        system(kClearConsoleBufferCommand);
    }
    
    int getInputInRange(const std::string &prompt, int min, int max)
    {
        int value = 0;
        bool validInput = false;

        while (!validInput)
        {
            std::cout << prompt;
            std::cin >> value;
            validInput = !std::cin.fail() && value >= min && value <= max;
            if (!validInput)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid entry. Must be between " << min << " and " << max << ".\n";
            }
        }
        return value;
    }

    void handleAllPlayers(dataModel::Board &board, std::vector<dataModel::Player> &players, GameAction::Action const &action)
    {
        for (auto &player : players)
        {
            std::cout << "\nHi player " << player.id << "! Let's see where you want to place your " << action.string << "! I'll show you the available locations\n";
            GameBoard::printBoard(board);
            switch (action.type)
            {
            case GameAction::ActionType::PlaceMines:
                GameMine::getCoordinates(player.remainingMines, player.mines, board);
                break;
            case GameAction::ActionType::MakeGuesses:
                GameMine::getCoordinates(GamePlayer::numberOfMinesToGuess(board, player, players), player.guesses, board);
                break;
            default:
                std::cerr << "Error: Unrecognized action type: " << static_cast<int>(action.type) << ".\n";
                break;
            }
            clearConsoleBuffer();
        }
    }



    void checkCollisions(dataModel::Board &board, std::vector<dataModel::Cell> const &coords, std::vector<dataModel::Player> &players)
    {
        for (dataModel::Cell const &coord : coords)
        {
            for (dataModel::Player &player : players)
            {
                for (dataModel::Cell const &mine : player.mines)
                {
                    if (GameMine::checkMinePosition(coord, mine))
                    {
                        GameMine::cancelMine(board, player, mine);
                    }
                }
            }
        }
    }

    void checkMinesSameLocation(dataModel::Board &board, std::vector<dataModel::Player> &players)
    {
        for (auto &player : players)
        {
            checkCollisions(board, player.mines, players);
        }
    }

    void checkGuesses(dataModel::Board &board, std::vector<dataModel::Player> &players)
    {
        for (auto &player : players)
        {
            checkCollisions(board, player.guesses, players);
        }
    }

    bool checkWinner(const std::vector<dataModel::Player> &players)
    {
        unsigned int i = 0;
        unsigned int actualPlayers = players.size();
        const dataModel::Player *winner = nullptr;
        bool gameOver = false;
        while (i < players.size() && !gameOver)
        {
            if (players[i].remainingMines == 0)
            {
                std::cout << "The player " << players[i].id << " has run out of mines.\n";
                actualPlayers--;
            }
            if (actualPlayers == 1)
            {
                winner = GamePlayer::getWinner(players);
                std::cout << "The winner is the player " << winner->id << "! Congratulations *confetti* *confetti* *confetti*";
                gameOver = true;
            }
            i++;
        }
        return gameOver;
    }

    void runMainLoop()
    {
        std::vector<dataModel::Player> players(0);
        dataModel::Board board;

        bool gameOver = false;

        GamePlayer::setupPlayers(players, GameMine::configureMines());
        GameBoard::configureBoard(board);

        while (!gameOver)
        {
            handleAllPlayers(board, players, GameAction::kActionPlaceMines);
            handleAllPlayers(board, players, GameAction::kActionMakeGuesses);

            checkMinesSameLocation(board, players);
            checkGuesses(board, players);

            gameOver = checkWinner(players);

            GamePlayer::resizeVectors(board, players);
        }
    }
}