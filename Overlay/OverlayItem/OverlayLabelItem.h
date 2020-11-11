/********************************************************************************
 *                                                                              *
 *  Overlay - OverlayLabelItem.h                                                *
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

#ifndef OVERLAY_OVERLAYLABELITEM_H
#define OVERLAY_OVERLAYLABELITEM_H

#include "OverlayBaseItem.h"
#include <string>

class OverlayLabelItem : public OverlayBaseItem {
private:
	xcb_gcontext_t xcbLabelCID{};
	xcb_font_t     xcbFont;
	std::string    sLabelText;
	uint32_t       uLabelColor;
	uint32_t       uSelectedLabelColor;
	uint32_t       uUnSelectedLabelColor;

public:
	explicit OverlayLabelItem(std::string labelText, uint32_t highlightedColor = DEFAULT_HIGHLIGHTED_COLOR,
							  uint32_t highlightedLabelColor = DEFAULT_NON_HIGHLIGHTED_COLOR,
							  uint32_t nonHighlightedColor = DEFAULT_NON_HIGHLIGHTED_COLOR,
							  uint32_t nonHighlightedLabelColor = DEFAULT_HIGHLIGHTED_COLOR,
							  int height = 0, int width = 0);

protected:
	void setup() override;

public:
	void initialize(xcb_connection_t *connection, xcb_screen_t *screen, int x, int y) override;
	
	void draw() override;
	
	void resetup() override;
	
	void set_highlighted() override;
	
	void set_non_highlighted() override;
	
	[[nodiscard]] std::string get_label_text() const;
	
	void set_label_text(std::string text);
	
	[[nodiscard]] uint32_t get_label_color() const;
	
	void set_label_color(uint32_t color);
	
	[[nodiscard]] uint32_t get_highlighted_label_color() const;
	
	void set_highlighted_label_color(uint32_t color);
	
	[[nodiscard]] uint32_t get_non_highlighted_label_color() const;
	
	void set_non_highlighted_label_color(uint32_t color);
};


#endif //OVERLAY_OVERLAYLABELITEM_H
