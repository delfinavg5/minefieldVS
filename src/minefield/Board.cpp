#include "Board.h"
#include "ColorLogic.h"

namespace GameBoard
{
    void printBoard(dataModel::Board const &board)
    {
        static int const kCellWidth = 3;
        static int const kBordersOffset = 3;
        std::size_t boardWidth = 0;
        int padding = 0;
        if (!board.matrix.empty())
        {
            boardWidth = board.matrix[0].size() * kCellWidth + kBordersOffset;
        }

        std::string title = MineColorLogic::applyColor(Color::Red, "GAME BOARD");
        if (boardWidth > 0)
        {
            padding = (boardWidth - title.length());
        }
        std::cout << std::setw(padding) << title << std::endl
                << std::endl;

        std::cout << "  ";
        for (unsigned int k = 0; k < board.matrix[0].size(); k++)
        {
            std::cout << std::setw(kCellWidth) << (k + 1);
        }
        std::cout << '\n';

        for (unsigned int i = 0; i < board.matrix.size(); i++)
        {
            std::cout << std::setw(2) << (i + 1) << " |";
            for (unsigned int j = 0; j < board.matrix[0].size(); j++)
            {
                std::cout << board.matrix[i][j] << std::setw(kCellWidth);
            }
            std::cout << '|' << std::endl;
        }
    }
    
    bool validPosition(dataModel::Board &board, int row, int column)
    {
        return ((row >= 0 && row < board.matrix.size()) && (column >= 0 && column < board.matrix[0].size()) && board.matrix[row][column] == 'O');
    }

    void configureBoard(dataModel::Board &board)
    {
        const int minSize = 24;
        const int maxSize = 50;
        static const std::string promptWidth = std::string("Enter the width you want the board to have, it must be between ") + std::to_string(minSize) + " and " + std::to_string(maxSize) + ".\n";
        static const std::string promptHigh = std::string("Enter the high you want the board to have, it must be between ") + std::to_string(minSize) + " and " + std::to_string(maxSize) + ".\n";
        int width = GameMinefield::getInputInRange(promptWidth, minSize, maxSize);
        int high = GameMinefield::getInputInRange(promptHigh, minSize, maxSize);

        board.matrix.resize(high, std::vector<char>(width, 'O'));
        std::cout << "The board is then printed as it looks, with the positions numbered:\n\n";
        printBoard(board);
    }
}