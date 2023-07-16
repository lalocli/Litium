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

#include "drawtextc.h"

#include "drawtext.hpp"

extern "C"
{

#include <stdint.h>

int64_t litium_api_drawtextc(const char *text, float x, float y, float size, float alpha, uint16_t color, unsigned int flags)
{
    return (litium_api_drawtext(text, x, y, size, alpha, color, flags));
}

}
