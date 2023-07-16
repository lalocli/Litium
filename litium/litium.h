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

#define LITIUM_VERSION "2023.7.15-0"
#define LITIUM_GAMEVERSION 38
#define LITIUM_GAMEVERSIONPATCH 'f'
#define LITIUM_GAMEVERSIONPATCH_DEDICATED 'e'

#if _WIN32
#define LITIUM_INLINE __forceinline
#elif __linux__
#define LITIUM_INLINE inline __attribute__((always_inline))
#endif
