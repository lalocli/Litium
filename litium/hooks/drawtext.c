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

#include "gamemain.h"

#include <stdarg.h>
#include <string.h>

#include "../addresses.h"
#include "../api/drawtextc.h"

#define NOFORMAT 0x40

subhook_t litium_hook_drawtext_k;

int64_t litium_hook_drawtext(const char *format, float x, float y, float size, unsigned int flags, float red, float green, float blue, float alpha, ...)
{
    va_list va;
    char buf[10000];

    if (LITIUM_RETURNADDRESS() == LITIUM_PLATFORMADDRESS(0x9658E, 0x15759D))
        return (litium_api_drawtextc("Generating...", x, y, size, 0xFFFF, LITIUM_API_TEXT_ALIGNCENTER));
    if (LITIUM_RETURNADDRESS() == LITIUM_PLATFORMADDRESS(0x966B4, 0x157629))
        return (litium_api_drawtextc("Connecting...", x, y, size, 0xFFFF, LITIUM_API_TEXT_ALIGNCENTER));

    // This is the original implementation for now, UNSAFE
    if ((flags & NOFORMAT) != 0)
        strcpy(buf, format);
    else
    {
        va_start(va, alpha);
        cs_format(buf, format, 10000, va);
    }

    subhook_remove(litium_hook_drawtext_k);
    int64_t ret = cs_drawtext(buf, x, y, size, flags | NOFORMAT, red, green, blue, alpha);
    subhook_install(litium_hook_drawtext_k);

    return (ret);
}
