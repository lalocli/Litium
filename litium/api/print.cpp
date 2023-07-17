/*
 * Litium: Lalo's Suitium
 * Copyright (C) 2023 Eduardo "lalocli"
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "print.hpp"

#include <iostream>
#include <stddef.h>
#include <string>
#include <sstream>

#if _WIN32
#include <windows.h>
#endif

#include "../addresses.h"

#define COLORMARK_INVALID -1
#define COLORMARK_RESET 0
#define COLORMARK_RED 1
#define COLORMARK_GREEN 2
#define COLORMARK_BLUE 3
#define COLORMARK_YELLOW 4
#define COLORMARK_CYAN 5
#define COLORMARK_PURPLE 6
#define COLORMARK_BOLD 8
#define COLORMARK_BLINK 9
#define COLORMARK_RAINBOW 16

int parsecolormark(const std::string &text, size_t *off)
{
    if (text[*off] != '<')
        return (COLORMARK_INVALID);

    std::stringstream stream;
    for (size_t count = (*off) + 1; count < text.size(); count++)
    {
        if (text[count] == '>')
        {
            *off = count;
            std::string result = stream.str();
            if (result == "reset")
                return (COLORMARK_RESET);
            else if (result == "red")
                return (COLORMARK_RED);
            else if (result == "green")
                return (COLORMARK_GREEN);
            else if (result == "blue")
                return (COLORMARK_BLUE);
            else if (result == "yellow")
                return (COLORMARK_YELLOW);
            else if (result == "cyan")
                return (COLORMARK_CYAN);
            else if (result == "purple")
                return (COLORMARK_PURPLE);
            else if (result == "bold")
                return (COLORMARK_BOLD);
            else if (result == "blink")
                return (COLORMARK_BLINK);
            else if (result == "rainbow")
                return (COLORMARK_RAINBOW);
            return (COLORMARK_INVALID);
        }

        stream << text[count];
    }

    return (COLORMARK_INVALID);
}

void litium_api_print(const std::string &text, const std::string &addon, const std::string &decoration)
{
    std::string actualtext;
    {
        std::stringstream stream;
        if (!addon.empty())
            stream << decoration << "[" << addon << "]:<reset> " << text;
        else
            stream << "[?]:<reset> " << text;
        actualtext = stream.str();
    }

    if (litium_isdedicated)
    {
#if _WIN32
        static HANDLE stdoutput = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
        GetConsoleScreenBufferInfo(stdoutput, &consoleinfo);
        WORD originalattributes = consoleinfo.wAttributes;

        WORD attributes = originalattributes;
        bool rainbow = false;

        for (size_t count = 0; count < actualtext.size(); count++)
        {
            if (actualtext[count] == '<')
            {
                switch (parsecolormark(actualtext, &count))
                {
                case COLORMARK_RESET:
                {
                    attributes = originalattributes;
                    rainbow = false;
                    break;
                }
                case COLORMARK_RED:
                {
                    attributes |= FOREGROUND_RED;
                    attributes &= ~FOREGROUND_GREEN;
                    attributes &= ~FOREGROUND_BLUE;
                    rainbow = false;
                    break;
                }
                case COLORMARK_GREEN:
                {
                    attributes &= ~FOREGROUND_RED;
                    attributes |= FOREGROUND_GREEN;
                    attributes &= ~FOREGROUND_BLUE;
                    rainbow = false;
                    break;
                }
                case COLORMARK_BLUE:
                {
                    attributes &= ~FOREGROUND_RED;
                    attributes &= ~FOREGROUND_GREEN;
                    attributes |= FOREGROUND_BLUE;
                    rainbow = false;
                    break;
                }
                case COLORMARK_YELLOW:
                {
                    attributes |= FOREGROUND_RED;
                    attributes |= FOREGROUND_GREEN;
                    attributes &= ~FOREGROUND_BLUE;
                    rainbow = false;
                    break;
                }
                case COLORMARK_PURPLE:
                {
                    attributes |= FOREGROUND_RED;
                    attributes &= ~FOREGROUND_GREEN;
                    attributes |= FOREGROUND_BLUE;
                    break;
                }
                case COLORMARK_CYAN:
                {
                    attributes &= ~FOREGROUND_RED;
                    attributes |= FOREGROUND_GREEN;
                    attributes |= FOREGROUND_BLUE;
                    break;
                }
                case COLORMARK_BOLD:
                {
                    // TODO: ?
                    break;
                }
                case COLORMARK_BLINK:
                {
                    // TODO: ?
                    break;
                }
                case COLORMARK_RAINBOW:
                {
                    rainbow = true;
                    break;
                }
                }

                SetConsoleTextAttribute(stdoutput, attributes);
            }
            else
                std::cout << actualtext[count];

            if (rainbow)
            {
                static const WORD colors[] = {
                    FOREGROUND_RED,
                    FOREGROUND_RED | FOREGROUND_GREEN,
                    FOREGROUND_GREEN,
                    FOREGROUND_BLUE,
                    FOREGROUND_RED | FOREGROUND_BLUE
                };
                SetConsoleTextAttribute(stdoutput, colors[count % (sizeof(colors) / sizeof(colors[0]))]);
            }
        }

        SetConsoleTextAttribute(stdoutput, originalattributes);
#elif __linux__
        bool bold = false;
        bool blink = false;
        bool rainbow = false;

        for (size_t count = 0; count < actualtext.size(); count++)
        {
            if (actualtext[count] == '<')
            {
                switch (parsecolormark(actualtext, &count))
                {
                case COLORMARK_RESET:
                {
                    bold = false;
                    blink = false;
                    rainbow = false;
                    std::cout << "\033[0m";
                    break;
                }
                case COLORMARK_RED:
                {
                    std::cout << "\033[31m";
                    rainbow = false;
                    break;
                }
                case COLORMARK_GREEN:
                {
                    std::cout << "\033[32m";
                    rainbow = false;
                    break;
                }
                case COLORMARK_BLUE:
                {
                    std::cout << "\033[34m";
                    break;
                }
                case COLORMARK_YELLOW:
                {
                    std::cout << "\033[33m";
                    rainbow = false;
                    break;
                }
                case COLORMARK_PURPLE:
                {
                    std::cout << "\033[35m";
                    rainbow = false;
                    break;
                }
                case COLORMARK_CYAN:
                {
                    std::cout << "\033[36m";
                    rainbow = false;
                    break;
                }
                case COLORMARK_BOLD:
                {
                    bold = true;
                    break;
                }
                case COLORMARK_BLINK:
                {
                    blink = true;
                    break;
                }
                case COLORMARK_RAINBOW:
                {
                    rainbow = true;
                    break;
                }
                }

                if (bold)
                    std::cout << "\033[1m";
                if (blink)
                    std::cout << "\033[5m";
            }
            else
                std::cout << actualtext[count];

            if (rainbow)
            {
                static const std::string colors[] = {
                    "31",
                    "33",
                    "32",
                    "36",
                    "34",
                    "35"
                };
                std::cout << "\033[" << colors[count % (sizeof(colors) / sizeof(colors[0]))] << 'm';
            }
        }

        std::cout << "\033[0m";
#endif
    }

    std::cout << std::endl;
}
