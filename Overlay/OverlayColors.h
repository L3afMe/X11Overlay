/********************************************************************************
 *                                                                              *
 *  Overlay - OverlayColors.h                                                   *
 *  Copyright (C) 2020 L3af                                                     *
 *                                                                              *
 *  This program is free software: you can redistribute it and/or modify it     *
 *  under the terms of the GNU General Public License as published by the       *
 *  Free Software Foundation, either version 3 of the License, or (at your      *
 *  option) any later version.                                                  *
 *                                                                              *
 *  This program is distributed in the hope that it will be useful, but         *
 *  WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See  the GNU General   *
 *  Public License for more details.                                            *
 *                                                                              *
 *  You should have received a copy of the GNU General Public License           *
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                              *
 ********************************************************************************/
#ifndef OVERLAY_OVERLAYCOLORS_H
#define OVERLAY_OVERLAYCOLORS_H

#include <cstdint>

#define Color_RED 0xFF0000
#define Color_GREEN 0x00FF00
#define Color_BLUE 0x0000FF
#define Color_BLACK 0x000000
#define Color_WHITE 0xFFFFFF

uint32_t rgb_to_uint(int red, int green, int blue);

uint32_t get_random_color();

#endif //OVERLAY_OVERLAYCOLORS_H
