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

#if __cplusplus
extern "C"
{
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#if _WIN32
#define LITIUM_PLATFORMADDRESS(windows, linux) windows
#define LITIUM_RETURNADDRESS() ((uintptr_t)_ReturnAddress() - litium_baseaddress)
#elif __linux__
#define LITIUM_PLATFORMADDRESS(windows, linux) linux
#define LITIUM_RETURNADDRESS() ((uintptr_t)__builtin_return_address(0) - litium_baseaddress)
#endif

/* ADDRESSES BEGIN */

extern uintptr_t litium_baseaddress;
extern bool litium_isdedicated;

extern int *litium_gameversionptr;
extern uint8_t *litium_gameversionpatchptr;

extern int64_t (*cs_drawtext)(const char *format, float x, float y, float size, unsigned int flags, float red, float green, float blue, float alpha, ...);
extern int64_t (*cs_format)(char *result, const char *format, int unk, va_list va);
extern void (*sr_gamemain)(void);

/* ADDRESSES END */

bool litium_map(uintptr_t baseptr);

#if __cplusplus
}
#endif
