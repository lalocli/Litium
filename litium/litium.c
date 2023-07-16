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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "addresses.h"
#include "hooks.h"
#include "litium.h"

bool litium_setup(uintptr_t baseptr)
{
    return (litium_map(baseptr) && litium_hook(baseptr));
}

#if _WIN32
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    char buf[256];

    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        if (!litium_setup((uintptr_t)GetModuleHandle(NULL)))
        {
            sprintf(buf, "Could not setup Litium.\nAre you sure you're running %d%c?\n", LITIUM_GAMEVERSION, LITIUM_GAMEVERSIONPATCH);
            MessageBox(NULL, buf, "Error", MB_OK | MB_ICONERROR);
            abort();
        }
        break;
    }
    }

    return (TRUE);
}
#elif __linux__
__attribute__((constructor)) void entry(void)
{
    FILE *mapfp;
    char *buf;
    size_t bufsz;
    uintptr_t baseptr;

    mapfp = fopen("/proc/self/maps", "rb");

    buf = NULL;
    bufsz = 0;
    while (1)
    {
        char c = fgetc(mapfp);
        if (c == '-' || c == EOF)
            break;
        buf = realloc(buf, ++bufsz);
        buf[bufsz - 1] = c;
    }

    sscanf(buf, "%p", &baseptr);

    if (!litium_setup(baseptr))
    {
        fprintf(stderr, "Could not setup Litium.\nAre you sure you're running %d%c?\n", LITIUM_GAMEVERSION, LITIUM_GAMEVERSIONPATCH);
        abort();
    }
}
#endif
