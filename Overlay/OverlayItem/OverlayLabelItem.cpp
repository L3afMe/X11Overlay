/********************************************************************************
 *                                                                              *
 *  Overlay - OverlayLabelItem.cpp.cc                                           *
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

#include "OverlayLabelItem.h"

OverlayLabelItem::OverlayLabelItem(std::string labelText, uint32_t highlightedColor, uint32_t highlightedLabelColor,
								   uint32_t nonHighlightedColor,
								   uint32_t nonHighlightedLabelColor, int height, int width)
		: OverlayBaseItem(highlightedColor, nonHighlightedColor, height, width),
		  sLabelText(std::move(labelText)),
		  uLabelColor(nonHighlightedLabelColor),
		  uUnSelectedLabelColor(nonHighlightedLabelColor),
		  uSelectedLabelColor(highlightedLabelColor) {}

void OverlayLabelItem::setup() {
	xcbFont = xcb_generate_id(xcbConnection);
	std::string font_name = "-misc-*";
	xcb_open_font(xcbConnection, xcbFont, font_name.size(), font_name.c_str());
	
	uint32_t maskValues[] = {get_label_color(), get_color(), xcbFont, 1, XCB_SUBWINDOW_MODE_INCLUDE_INFERIORS};
	xcb_create_gc(xcbConnection, xcbLabelCID, xcbWindow, XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT |
														 XCB_GC_GRAPHICS_EXPOSURES | XCB_GC_SUBWINDOW_MODE, maskValues);
	OverlayBaseItem::setup();
}

void OverlayLabelItem::resetup() {
	xcb_free_gc(xcbConnection, xcbLabelCID);
	OverlayBaseItem::resetup();
}

void OverlayLabelItem::initialize(xcb_connection_t *connection, xcb_screen_t *screen, int x, int y) {
	xcbLabelCID = xcb_generate_id(connection);
	OverlayBaseItem::initialize(connection, screen, x, y);
}

void OverlayLabelItem::draw() {
	xcb_rectangle_t rectangles[] = {{static_cast<int16_t>(nPosX), static_cast<int16_t>(nPosY), static_cast<uint16_t>(nWidth), static_cast<uint16_t>(nHeight)}};
	xcb_poly_fill_rectangle(xcbConnection, xcbWindow, xcbCID, 1, rectangles);
	xcb_flush(xcbConnection);
	xcb_image_text_8(xcbConnection, get_label_text().size(), xcbWindow, xcbLabelCID,
					 nPosX + 5, nPosY + 5 + nHeight / 2, get_label_text().c_str());
	xcb_flush(xcbConnection);
}

void OverlayLabelItem::set_highlighted() {
	set_label_color(get_highlighted_label_color());
	OverlayBaseItem::set_highlighted();
}

void OverlayLabelItem::set_non_highlighted() {
	set_label_color(get_non_highlighted_label_color());
	OverlayBaseItem::set_non_highlighted();
}

std::string OverlayLabelItem::get_label_text() const {
	return sLabelText;
}

void OverlayLabelItem::set_label_text(std::string text) {
	sLabelText = std::move(text);
}

uint32_t OverlayLabelItem::get_label_color() const {
	return uLabelColor;
}

void OverlayLabelItem::set_label_color(uint32_t color) {
	uLabelColor = color;
}

uint32_t OverlayLabelItem::get_highlighted_label_color() const {
	return uSelectedLabelColor;
}

void OverlayLabelItem::set_highlighted_label_color(uint32_t color) {
	uSelectedLabelColor = color;
}

uint32_t OverlayLabelItem::get_non_highlighted_label_color() const {
	return uUnSelectedLabelColor;
}

void OverlayLabelItem::set_non_highlighted_label_color(uint32_t color) {
	uUnSelectedLabelColor = color;
}
