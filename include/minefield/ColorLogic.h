#pragma once
#include <string>

enum class Color
{
    Red,
};
namespace MineColorLogic
{
    std::string applyColorWindows(std::string const &toMessage);
    char const *const colorString(Color forColor);
    std::string applyColorPosix(Color color, std::string const &toMessage);
    std::string applyColor(Color color, std::string const &toMessage);
}