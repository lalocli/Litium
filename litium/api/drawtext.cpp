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

#include "drawtext.hpp"

#include <stdint.h>
#include <string>

#include "../addresses.h"
#include "../litium.h"

#define NOFORMAT 0x40

int64_t litium_api_drawtext(const std::string &text, float x, float y, float size, float alpha, uint16_t color, unsigned int flags)
{
    float red, green, blue;
    red = ((float)((color & 0x0F00) >> 8)) / 16.0f;
    green = ((float)((color & 0x00F0) >> 4)) / 16.0f;
    blue = ((float)((color & 0x000F))) / 16.0f;

    return (cs_drawtext(litium_makesafestr(text).c_str(), x, y, size, flags | NOFORMAT, red, green, blue, alpha));
}
