/********************************************************************************
 *                                                                              *
 *  Overlay - Overlay.cpp                                                       *
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
#include "Overlay.h"

#include <iostream>

Overlay::Overlay(int x, int y, int width, int height) : nPosX(x), nPosY(y), nWidth(width), nHeight(height) {
	xcbConnection = xcb_connect(nullptr, nullptr);
	xcbScreen     = xcb_setup_roots_iterator(xcb_get_setup(xcbConnection)).data;
}

void Overlay::start() {
	int ptcr = pthread_create(&pOverlayThread, nullptr, (THREADFUNCPTR) &thread_loop, (void *) this);
	
	if(ptcr) {
		throw (OverlayExcept("Error:unable to create thread," + std::to_string(ptcr)));
	}
	
	pthread_join(pOverlayThread, (void **) nullptr);
}

void Overlay::stop() {
	bRunThread = false;
}

void *Overlay::thread_loop(void *arg) {
	auto                *overlay   = (Overlay *) arg;
	bool                wasVisible = false;
	Display             *display   = XOpenDisplay(":0");
	while (overlay->bRunThread) {
		auto &toggleVisPressedKey = overlay->tPressedKeys[2];
		if(is_key_down(display, XK_Super_R)) {
			if(!std::get<0>(toggleVisPressedKey)) {
				std::get<0>(toggleVisPressedKey) = true;
				overlay->set_visible(!overlay->is_visible());
			}
		} else {
			std::get<0>(toggleVisPressedKey) = false;
		}
		
		if(overlay->bVisible) {
			wasVisible = true;
			
			auto &upPressedKey = overlay->tPressedKeys[0];
			if(is_key_down(display, XK_Up)) {
				if(std::get<0>(upPressedKey)) {
					if(float(clock() - std::get<1>(upPressedKey)) / CLOCKS_PER_SEC >
					   std::max(0.125 * std::get<2>(upPressedKey), 0.05)) {
						std::get<0>(upPressedKey) = false;
						std::get<2>(upPressedKey) -= 0.15;
					}
				}
				
				if(!std::get<0>(upPressedKey)) {
					std::get<0>(upPressedKey) = true;
					std::get<1>(upPressedKey) = clock();
					overlay->select_up();
				}
			} else {
				std::get<0>(upPressedKey) = false;
				std::get<2>(upPressedKey) = 1;
			}
			
			auto &downPressedKey = overlay->tPressedKeys[1];
			if(is_key_down(display, XK_Down)) {
				if(std::get<0>(downPressedKey)) {
					if(float(clock() - std::get<1>(downPressedKey)) / CLOCKS_PER_SEC >
					   std::max(0.125 * std::get<2>(downPressedKey), 0.05)) {
						std::get<0>(downPressedKey) = false;
						std::get<2>(downPressedKey) -= 0.15;
					}
				}
				
				if(!std::get<0>(downPressedKey)) {
					std::get<0>(downPressedKey) = true;
					std::get<1>(downPressedKey) = clock();
					overlay->select_down();
				}
			} else {
				std::get<0>(downPressedKey) = false;
				std::get<2>(downPressedKey) = 1;
			}
			
			overlay->draw();
		} else {
			if(wasVisible) {
				system("xrefresh");
				wasVisible = false;
			}
		}
	}
	XCloseDisplay(display);
	
	return nullptr;
}

bool Overlay::is_key_down(Display *display, KeySym key) {
	char keys_return[32];
	XQueryKeymap(display, keys_return);
	KeyCode kc2 = XKeysymToKeycode(display, key);
	return !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
}

const std::vector<OverlayBaseItem *> &Overlay::get_items() const {
	return vItems;
}

void Overlay::set_selected(int index) {
	vItems[nSelectedIndex]->set_non_highlighted();
	nSelectedIndex = std::max(0, std::min(index, (int) vItems.size() - 1));
	vItems[nSelectedIndex]->set_highlighted();
}

int Overlay::get_selected() const {
	return nSelectedIndex;
}

void Overlay::select_up() {
	if(!vItems.empty()) {
		set_selected(nSelectedIndex - 1 < 0 ? (int) vItems.size() - 1 : nSelectedIndex - 1);
	}
}

void Overlay::select_down() {
	if(!vItems.empty()) {
		set_selected(nSelectedIndex + 1 == vItems.size() ? 0 : nSelectedIndex + 1);
	}
}

void Overlay::set_visible(bool visible) {
	bVisible = visible;
	system("xrefresh");
}

bool Overlay::is_visible() const {
	return bVisible;
}

void Overlay::draw() {
	if(!vItems.empty()) {
		for (OverlayBaseItem *item : vItems) {
			item->draw();
		}
	}
}

void Overlay::dispose() {
	for (OverlayBaseItem *item : vItems) {
		item->dispose();
	}
	xcb_disconnect(xcbConnection);
}

void Overlay::add_item(OverlayBaseItem *item) {
	int bottomY = vItems.empty() ? nPosY : vItems[vItems.size() - 1]->get_pos_y() +
										   vItems[vItems.size() - 1]->get_height();
	
	if(item->get_height() == 0) {
		item->set_height(nHeight);
	}
	
	if(item->get_width() == 0) {
		item->set_width(nWidth);
	}
	
	item->initialize(xcbConnection, xcbScreen, nPosX, bottomY);
	vItems.push_back(item);
	
	if(vItems.size() == 1) {
		vItems[0]->set_highlighted();
	}
}
