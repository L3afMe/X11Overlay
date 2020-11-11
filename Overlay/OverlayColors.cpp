/********************************************************************************
 *                                                                              *
 *  Overlay - OverlayColors.cpp                                                 *
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
#include <cstdlib>
#include "OverlayColors.h"

uint32_t rgb_to_uint(int red, int green, int blue) {
	return (255 << 24) + (red << 16) + (green << 8) + blue;
}

uint32_t get_random_color() {
	return rgb_to_uint((int)random() % 255, (int)random() % 255, (int)random() % 255);
}
