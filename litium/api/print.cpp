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
#include <string>

#include "../addresses.h"

void litium_api_print(const std::string &text, const std::string &addon)
{
    if (litium_isdedicated)
    {
        std::string prefix = "[?]: ";
        if (!addon.empty())
        {
            prefix = "[";
            prefix += addon + "]: ";
        }

        std::cout << prefix << text << std::endl;
    }
}
