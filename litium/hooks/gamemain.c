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

#include "../../subhook/subhook.h"
#include "../addresses.h"

subhook_t litium_hook_gamemain_k;

void litium_hook_gamemain(void)
{
    subhook_remove(litium_hook_gamemain_k);

    sr_gamemain();

    subhook_install(litium_hook_gamemain_k);
}
