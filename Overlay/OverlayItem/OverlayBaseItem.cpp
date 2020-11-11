/********************************************************************************
 *                                                                              *
 *  Overlay - OverlayBaseItem.cpp                                                      *
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
#include "OverlayBaseItem.h"

OverlayBaseItem::OverlayBaseItem(uint32_t highlightedColor, uint32_t nonHighlightedColor, int height, int width) :
		uColor(nonHighlightedColor), uNonHighlightedColor(nonHighlightedColor), uHighlightedColor(highlightedColor), nHeight(height), nWidth(width) {}

void OverlayBaseItem::initialize(xcb_connection_t *connection, xcb_screen_t *screen, int x, int y) {
	xcbConnection = connection;
	nPosX         = x;
	nPosY         = y;
	xcbWindow     = screen->root;
	xcbCID        = xcb_generate_id(xcbConnection);
	
	setup();
}

void OverlayBaseItem::draw() {
	xcb_rectangle_t rectangles[] = {{static_cast<int16_t>(nPosX), static_cast<int16_t>(nPosY), static_cast<uint16_t>(nWidth), static_cast<uint16_t>(nHeight)},};
	xcb_poly_fill_rectangle(xcbConnection, xcbWindow, xcbCID, 1, rectangles);
	xcb_flush(xcbConnection);
}

void OverlayBaseItem::dispose() {
	xcb_kill_client_checked(xcbConnection, xcbCID);
}

void OverlayBaseItem::setup() {
	uint32_t maskValues[] = {uColor, XCB_SUBWINDOW_MODE_INCLUDE_INFERIORS};
	xcb_create_gc(xcbConnection, xcbCID, xcbWindow, XCB_GC_FOREGROUND | XCB_GC_SUBWINDOW_MODE, maskValues);
}

void OverlayBaseItem::set_highlighted() {
	set_color(get_highlighted_color());
	resetup();
}

void OverlayBaseItem::set_non_highlighted() {
	set_color(get_non_highlighted_color());
	resetup();
}

void OverlayBaseItem::resetup() {
	xcb_free_gc(xcbConnection, xcbCID);
	setup();
}

uint32_t OverlayBaseItem::get_color() const {
	return uColor;
}

void OverlayBaseItem::set_color(uint32_t color) {
	uColor = color;
}

uint32_t OverlayBaseItem::get_highlighted_color() const {
	return uHighlightedColor;
}

void OverlayBaseItem::set_highlighted_color(uint32_t color) {
	uHighlightedColor = color;
}

uint32_t OverlayBaseItem::get_non_highlighted_color() const {
	return uNonHighlightedColor;
}

void OverlayBaseItem::set_non_highlighted_color(uint32_t color) {
	uNonHighlightedColor = color;
}

int OverlayBaseItem::get_pos_x() const {
	return nPosX;
}

void OverlayBaseItem::set_pos_x(int x) {
	nPosX = x;
}

int OverlayBaseItem::get_pos_y() const {
	return nPosY;
}

void OverlayBaseItem::set_pos_y(int y) {
	nPosY = y;
}

int OverlayBaseItem::get_width() const {
	return nWidth;
}

void OverlayBaseItem::set_width(int width) {
	nWidth = width;
}

int OverlayBaseItem::get_height() const {
	return nHeight;
}

void OverlayBaseItem::set_height(int height) {
	nHeight = height;
}
