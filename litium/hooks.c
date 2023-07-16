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

#include "hooks.h"

#include <stdbool.h>
#include <stdint.h>

#include "../subhook/subhook.h"
#include "addresses.h"

#include "hooks/drawmenu.c"
#include "hooks/drawtext.c"
#include "hooks/gamemain.c"

#define HOOK(src, dst, k) \
    { \
    if (src != NULL) \
        { \
            k = subhook_new(src, dst, SUBHOOK_64BIT_OFFSET); \
            if (subhook_install(k) != 0) \
                return (0); \
        } \
    }

bool litium_hook(uintptr_t baseptr)
{
    HOOK(cs_drawtext, litium_hook_drawtext, litium_hook_drawtext_k);
    HOOK(sr_drawmenu, litium_hook_drawmenu, litium_hook_drawmenu_k);
    HOOK(sr_gamemain, litium_hook_gamemain, litium_hook_gamemain_k);

    return (true);
}
