#include "Mine.h"


namespace GameMine
{
    int configureMines()
    {
        const int minMines = 3;
        const int maxMines = 8;
        static const std::string prompt = std::string("Enter the number of mines you want to play with, it must be between ") + std::to_string(minMines) + " and " + std::to_string(maxMines) + ".\n";

        return GameMinefield::getInputInRange(prompt, minMines, maxMines);
    }
    void getCoordinates(int numberOfMines, std::vector<dataModel::Cell> &mines, dataModel::Board &board)
    {
        int auxX = 0;
        int auxY = 0;
        int i = 0;

        while (i < numberOfMines)
        {
            std::cout << "Enter the coordinates of the mine " << (i + 1) << ": " << std::endl;

            std::cout << "Enter the X coordinate:\n";
            std::cin >> auxX;
            auxX--;

            std::cout << "Enter the Y coordinate:\n";
            std::cin >> auxY;
            auxY--;

            if (GameBoard::validPosition(board, auxX, auxY))
            {
                mines[i].row = auxX;
                mines[i].column = auxY;
                i++;
            }
            else
            {
                std::cout << "The coordinate is not valid." << std::endl;
            }
        }
    }

    bool checkMinePosition(dataModel::Cell const &mine1, dataModel::Cell const &mine2)
    {
        return ((mine1.row == mine2.row) && (mine1.column == mine2.column));
    }

    void cancelMine(dataModel::Board &board, dataModel::Player &player, dataModel::Cell const &mineToErase)
    {
        static const char xBoard = 'X';
        int mineIndex = -1;

        auto iter = player.mines.begin();
        for (; iter != player.mines.end(); iter++)
        {
            if (checkMinePosition(*iter, mineToErase))
            {
                board.matrix[iter->row][iter->column] = xBoard;
                player.mines.erase(iter);
                player.remainingMines--;
                break;
            }
        }
    }
};