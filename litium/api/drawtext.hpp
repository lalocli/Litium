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

#pragma once

#include <stdint.h>
#include <string>

#ifndef LITIUM_API_TEXT_ALIGNRIGHT
#define LITIUM_API_TEXT_ALIGNRIGHT 0x0
#define LITIUM_API_TEXT_ALIGNCENTER 0x1
#define LITIUM_API_TEXT_ALIGNLEFT 0x2
#define LITIUM_API_TEXT_ALIGNUP 0x4
#define LITIUM_API_TEXT_ALIGNDOWN 0x8
#define LITIUM_API_TEXT_SHADOWS 0x20
#endif

/*
 * Draws a text on the screen.
 * Uses a RGB color hex where the lowest place is blue.
*/
int64_t litium_api_drawtext(const std::string &text, float x, float y, float size, float alpha = 1.0f, uint16_t color = 0x0FFF, unsigned int flags = LITIUM_API_TEXT_ALIGNRIGHT);
