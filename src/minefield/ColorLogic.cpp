#include "ColorLogic.h"
#include <string>

namespace MineColorLogic
{
    std::string applyColorWindows(std::string const &toMessage)
    {
        return toMessage;
    }

    char const *const colorString(Color forColor)
    {
        auto colorTranslation = "InvalidColor";
        switch (forColor)
        {
        case Color::Red:
            colorTranslation = "\033[1;31m";
            break;
        default:
            colorTranslation = "Another Color";
            break;
        }
        return colorTranslation;
    }

    std::string applyColorPosix(Color color, std::string const &toMessage)
    {
        static char const *const kResetColor = "\033[0m";
        return std::string{colorString(color)} + toMessage + kResetColor;
    }

    std::string applyColor(Color color, std::string const &toMessage)
    {
    #ifdef WIN32
        return applyColorWindows(toMessage);
    #else
        return applyColorPosix(color, toMessage);
    #endif
    }
}