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

#include "drawmenu.h"

#include <stdio.h>

#include "../../subhook/subhook.h"
#include "../api/drawtextc.h"
#include "../addresses.h"
#include "../litium.h"

subhook_t litium_hook_drawmenu_k;

int litium_hook_drawmenu(int unk)
{
    char buf[256];
    int ret;

    if (!*sr_isingameptr)
    {
        if (*sr_menuidptr == 0)
        {
            sprintf(buf, "Sub Rosa 0.%d%c", *sr_gameversionptr, *sr_gameversionpatchptr + 97);
            litium_api_drawtextc(buf, 512.0f, 128.0f, 24.0f, 1.0f, 0x0FFF, LITIUM_API_TEXT_ALIGNCENTER);
            sprintf(buf, "Litium %s", LITIUM_VERSION);
            litium_api_drawtextc(buf, 512.0f, 128.0f + 22.0f, 16.0f, 1.0f, 0x07AF, LITIUM_API_TEXT_ALIGNCENTER);
        }
    }

    subhook_remove(litium_hook_drawmenu_k);
    ret = sr_drawmenu(unk);
    subhook_install(litium_hook_drawmenu_k);

    return (ret);
}
