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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "structs/vehicletype.h"

#if __cplusplus
extern "C"
{
#endif

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

extern int *sr_gameversionptr;
extern uint8_t *sr_gameversionpatchptr;

extern bool *sr_isingameptr;
extern int *sr_menuidptr;

extern sr_vehicletype_t *sr_vehicletypes;

extern int64_t (*cs_drawtext)(const char *format, float x, float y, float size, unsigned int flags, float red, float green, float blue, float alpha, ...);
extern int64_t (*cs_format)(char *result, const char *format, int unk, va_list va);
extern int (*sr_drawmenu)(int unk);
extern void (*sr_gamemain)(void);
#if _WIN32
extern int (*sr_printf)(const char *format, ...);
#elif __linux__
extern int (*sr_printf)(int flag, const char *format, ...);
extern int (*sr_puts)(const char *str);
#endif

/* ADDRESSES END */

bool litium_map(uintptr_t baseptr);

#if __cplusplus
}
#endif
