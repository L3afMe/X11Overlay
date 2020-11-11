/********************************************************************************
 *                                                                              *
 *  Overlay - Overlay.h                                                         *
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
#ifndef OVERLAY_OVERLAY_H
#define OVERLAY_OVERLAY_H

#include "OverlayItem/OverlayBaseItem.h"
#include "OverlayItem/OverlayLabelItem.h"
#include "OverlayExcept.h"
#include "OverlayColors.h"
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <exception>
#include <pthread.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <tuple>

typedef void *(*THREADFUNCPTR)(void *);

class Overlay {
private:
	pthread_t                      pOverlayThread;
	xcb_connection_t               *xcbConnection;
	xcb_screen_t                   *xcbScreen;
	std::vector<OverlayBaseItem *> vItems;
	int                            nPosX;
	int                            nPosY;
	int                            nWidth;
	int                            nHeight;
	int                            nSelectedIndex  = 0;
	bool                           bVisible        = true;
	bool                           bRunThread      = true;
	std::tuple<bool, long, double> tPressedKeys[4] = {
			std::make_tuple(false, clock(), 1.0),
			std::make_tuple(false, clock(), 1.0),
			std::make_tuple(false, clock(), 1.0),
			std::make_tuple(false, clock(), 1.0)};

private:
	static void *thread_loop(void *arg);
	
	static bool is_key_down(Display *display, KeySym key);

public:
	explicit Overlay(int x, int y, int width, int height);
	
	void start();
	
	void stop();
	
	void set_selected(int index);
	
	[[nodiscard]] int get_selected() const;
	
	void select_up();
	
	void select_down();
	
	void set_visible(bool visible);
	
	[[nodiscard]] bool is_visible() const;
	
	void draw();
	
	void dispose();
	
	void add_item(OverlayBaseItem *item);
	
	[[nodiscard]] const std::vector<OverlayBaseItem *> &get_items() const;
};

#endif //OVERLAY_OVERLAY_H
