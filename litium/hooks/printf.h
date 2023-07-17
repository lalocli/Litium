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

#include "../../subhook/subhook.h"

extern subhook_t litium_hook_printf_k;
#if _WIN32
int litium_hook_printf(const char *format, ...);
#elif __linux__
int litium_hook_printf(int flag, const char *format, ...);
#endif

#if __linux__
extern subhook_t litium_hook_puts_k;
int litium_hook_puts(const char *str);
#endif
