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

#include <stdbool.h>
#include <stdint.h>

#if __cplusplus
#include <stdio.h>
#include <string>
#include <string.h>
#endif

#include "../litium.h"

#if __cplusplus
extern "C"
{
#endif

#define SR_NUMOFVEHICLETYPES 17

struct sr_vehicletype
{
    bool usesexternalmodel;
    LITIUM_PAD(3);
    bool usesunstablephysics;
    LITIUM_PAD(3);
    int32_t controllertypenum;
    LITIUM_PAD(8);
    char name[32];
    int32_t price;
    float mass;
    LITIUM_PAD(99716);

#if __cplusplus
    LITIUM_INLINE size_t index() const
    {
        extern sr_vehicletype *sr_vehicletypes;
        return (((uintptr_t)this - (uintptr_t)sr_vehicletypes) / sizeof(sr_vehicletype));
    }

    LITIUM_INLINE std::string name_str() const
    {
        return (this->name);
    }
    LITIUM_INLINE void set_name(const std::string &name)
    {
        memset(this->name, 0, 32); // not sure if string.copy returns a null terminated string
        litium_makesafestr(name).copy(this->name, 31);
    }

    std::string str() const
    {
        char buf[256];
        sprintf(buf, "%s %zu", this->name, this->index());
        return (buf);
    }
#endif
};
typedef struct sr_vehicletype sr_vehicletype_t;

#if __cplusplus
}
#endif
