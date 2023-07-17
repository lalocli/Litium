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

#include "printf.h"

#include <stdio.h>
#include <string.h>

#include "../../subhook/subhook.h"
#include "../api/printc.h"

subhook_t litium_hook_printf_k;

#if _WIN32
int litium_hook_printf(const char *format, ...)
#elif __linux__
int litium_hook_printf(int flag, const char *format, ...)
#endif
{
    va_list va;
    char buf[512];
    int ret;

    if (strcmp(format, "connection successful\n") == 0)
        format = "<green>Connection successful!\n";
    else if (strcmp(format, "connection failed\n") == 0)
        format = "<blink><bold><red>Connection failed!\n";
    else if (strcmp(format, "port:%d\n") == 0)
        format = "Port: %u.\n";
    else if (strcmp(format, "socketenabled:%d\n") == 0)
    {
        va_start(va, format);
        format = va_arg(va, int) ? "Socket status: <green>OK<reset>.\n" : "Socket status: <red>?\n";
        va_end(va);
    }

    va_start(va, format);
    ret = vsprintf(buf, format, va);
    va_end(va);

    buf[ret - 1] = 0;
    litium_api_printc(buf, "Sub Rosa", "<bold><purple>");

    return (ret);
}


#if __linux__
subhook_t litium_hook_puts_k;
int litium_hook_puts(const char *str)
{
    char buf[256];

    strcpy(buf, str);
    strcat(buf, "\n");
    return (litium_hook_printf(1, buf));
}
#endif
