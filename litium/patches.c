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

#include "patches.h"

#if _WIN32
#include <windows.h>
#elif __linux__
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

#include "addresses.h"

#if __linux__
#define PAGE_READONLY           0x02
#define PAGE_READWRITE          0x04
#define PAGE_EXECUTE            0x10
#define PAGE_EXECUTE_READ       0x20
#define PAGE_EXECUTE_READWRITE  0x40
#endif

#define NOP(address, size) memset(address, 0x90, size)

#if __linux__
int VirtualProtect(void *address, size_t size, int protection, int *oldProtection)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    void *alignedAddress = (void *)((uintptr_t)address & ~(pagesize - 1));

    int prot = PROT_NONE;
    if (protection == PAGE_READONLY)
        prot = PROT_READ;
    if (protection == PAGE_READWRITE)
        prot = PROT_READ | PROT_WRITE;
    if (protection == PAGE_EXECUTE)
        prot = PROT_EXEC;
    if (protection == PAGE_EXECUTE_READ)
        prot = PROT_READ | PROT_EXEC;
    if (protection == PAGE_EXECUTE_READWRITE)
        prot = PROT_READ | PROT_WRITE | PROT_EXEC;

    mprotect(alignedAddress, pagesize, prot);

    if (oldProtection != NULL)
        *oldProtection = protection;

    return (1);
}
#endif

void litium_patch(void)
{
    uintptr_t baseptr;
    int oldprotect;

    baseptr = litium_baseaddress;

#if _WIN32
    // Menu ID patch
    if (!litium_isdedicated)
    {
        VirtualProtect((void *)(baseptr + 0x96C2E), 7, PAGE_EXECUTE_READWRITE, &oldprotect);
        NOP((uint8_t *)(baseptr + 0x96C2E), 7);
        VirtualProtect((void *)(baseptr + 0x96C2E), 7, oldprotect, &oldprotect);
    }
#elif __linux__
// Menu ID patch
    if (!litium_isdedicated)
    {
        VirtualProtect((void *)(baseptr + 0x158FC8), 10, PAGE_EXECUTE_READWRITE, &oldprotect);
        NOP((uint8_t *)(baseptr + 0x158FC8), 10);
        VirtualProtect((void *)(baseptr + 0x158FC8), 10, oldprotect, &oldprotect);
    }
#endif
}
