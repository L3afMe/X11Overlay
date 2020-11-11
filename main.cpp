/********************************************************************************
 *                                                                              *
 *  Overlay - main.cpp                                                          *
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
#include <iostream>
#include "Overlay/Overlay.h"

int main() {
	try {
		auto *overlay = new Overlay(50, 50, 100, 25);
		
		overlay->add_item(new OverlayLabelItem("Option 1", Color_WHITE, Color_BLACK, Color_BLACK, Color_WHITE));
		overlay->add_item(new OverlayLabelItem("Option 2"));
		overlay->add_item(new OverlayLabelItem("Option 3"));
		overlay->add_item(new OverlayLabelItem("Option 4"));
		overlay->add_item(new OverlayLabelItem("Option 5"));
		
		overlay->start();
	} catch (OverlayExcept &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}
