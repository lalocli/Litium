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

#include "addresses.h"

#include <stdbool.h>
#include <stdint.h>

#include "litium.h"

#define PTR(ptr) (void *)(ptr)

/* ADDRESSES BEGIN */

uintptr_t litium_baseaddress;
bool litium_isdedicated;

int *sr_gameversionptr;
uint8_t *sr_gameversionpatchptr;

bool *sr_isingameptr;
int *sr_menuidptr;

int64_t (*cs_drawtext)(const char *format, float x, float y, float size, unsigned int flags, float red, float green, float blue, float alpha, ...);
int64_t (*cs_format)(char *result, const char *format, int unk, va_list va);
int (*sr_drawmenu)(int unk);
void (*sr_gamemain)(void);

/* ADDRESSES END */

bool litium_map(uintptr_t baseptr)
{
    litium_baseaddress = baseptr;

label_client: {}
    sr_gameversionptr = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x2B231C, 0x389888));
    sr_gameversionpatchptr = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x2B23DC, 0x389884));
    if (*sr_gameversionptr != LITIUM_GAMEVERSION || *sr_gameversionpatchptr != LITIUM_GAMEVERSIONPATCH - 97)
        goto label_dedicated;

    sr_isingameptr = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x43EBFAA0, 0x1CE18FE0));
    sr_menuidptr = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x43EBFAA4, 0x1CE18FE4));

    cs_drawtext = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x6D930, 0x2C62C));
    cs_format = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x6E530, 0x238F5));
    sr_drawmenu = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x72450, 0x30821));
    sr_gamemain = PTR(baseptr + LITIUM_PLATFORMADDRESS(0x96440, 0x15745C));

    litium_isdedicated = false;
    return (true);

label_dedicated: {}
    sr_gameversionptr = PTR(baseptr + LITIUM_PLATFORMADDRESS(0xF7ADC, 0x0)); // This is probably not the real address, but the only read only data I could find containing the right value
    sr_gameversionpatchptr = PTR(baseptr + LITIUM_PLATFORMADDRESS(0xF79DC, 0x0)); // This is probably not the real address, but the only read only data I could find containing the right value
    if (*sr_gameversionptr != LITIUM_GAMEVERSION || *sr_gameversionpatchptr != LITIUM_GAMEVERSIONPATCH_DEDICATED - 97)
        return (false);

    sr_isingameptr = PTR(0);
    sr_menuidptr = PTR(0);

    cs_drawtext = PTR(0);
    cs_format = PTR(0);
    sr_drawmenu = PTR(0);
    sr_gamemain = PTR(0);

    litium_isdedicated = true;
    return (true);
}
