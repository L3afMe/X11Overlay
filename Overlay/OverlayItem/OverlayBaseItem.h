/********************************************************************************
 *                                                                              *
 *  Overlay - OverlayBaseItem.h                                                        *
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
#ifndef OVERLAY_OVERLAYBASEITEM_H
#define OVERLAY_OVERLAYBASEITEM_H

#include <cstdint>
#include <xcb/xcb.h>
#include "../OverlayColors.h"

#define DEFAULT_NON_HIGHLIGHTED_COLOR Color_BLACK
#define DEFAULT_HIGHLIGHTED_COLOR Color_WHITE

class OverlayBaseItem {
protected:
	xcb_connection_t *xcbConnection{};
	xcb_gcontext_t   xcbCID{};
	xcb_drawable_t   xcbWindow{};
	uint32_t         uColor;
	uint32_t         uHighlightedColor;
	uint32_t         uNonHighlightedColor;
	int              nPosX{};
	int              nPosY{};
	int              nWidth;
	int              nHeight;

public:
	explicit OverlayBaseItem(uint32_t highlightedColor = DEFAULT_HIGHLIGHTED_COLOR,
							 uint32_t nonHighlightedColor = DEFAULT_NON_HIGHLIGHTED_COLOR, int height = 0, int width = 0);

protected:
	virtual void setup();

public:
	virtual void initialize(xcb_connection_t *connection, xcb_screen_t *screen, int x, int y);
	
	virtual void draw();
	
	virtual void dispose();
	
	virtual void resetup();
	
	virtual void set_highlighted();
	
	virtual void set_non_highlighted();
	
	[[nodiscard]] virtual uint32_t get_color() const;
	
	virtual void set_color(uint32_t color);
	
	[[nodiscard]] virtual uint32_t get_highlighted_color() const;
	
	virtual void set_highlighted_color(uint32_t color);
	
	[[nodiscard]] virtual uint32_t get_non_highlighted_color() const;
	
	virtual void set_non_highlighted_color(uint32_t color);
	
	[[nodiscard]] virtual int get_pos_x() const;
	
	virtual void set_pos_x(int x);
	
	[[nodiscard]] virtual int get_pos_y() const;
	
	virtual void set_pos_y(int y);
	
	[[nodiscard]] virtual int get_width() const;
	
	virtual void set_width(int width);
	
	[[nodiscard]] virtual int get_height() const;
	
	virtual void set_height(int height);
};


#endif //OVERLAY_OVERLAYBASEITEM_H
