/*
 * Copyright 2018 Jared Boone
 *
 * This file is part of HackRF.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "ui_portapack.h"

#include "portapack.h"

/* Pixel data within a font or bitmap byte is "reversed": LSB is left-most pixel. */

static const uint8_t font_fixed_8x16_glyph_data[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x24,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48,
	0x48, 0x48, 0xff, 0x24, 0x24, 0xff, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x78, 0x14, 0x14, 0x14, 0x18, 0x30, 0x50, 0x50, 0x50, 0x3c, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x29, 0x29, 0x19, 0x16, 0x68, 0x98, 0x94,
	0x94, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x14, 0x88,
	0x54, 0x72, 0x22, 0x62, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
	0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08,
	0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x08, 0x2a, 0x1c, 0x2a, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
	0x10, 0x10, 0xfe, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x10, 0x10,
	0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
	0x24, 0x42, 0x42, 0x5a, 0x5a, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0c, 0x0a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x20, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04,
	0x02, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x20, 0x20, 0x10, 0x0c,
	0x10, 0x20, 0x20, 0x10, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30,
	0x28, 0x28, 0x24, 0x24, 0x22, 0x7e, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x04, 0x04, 0x04, 0x3c, 0x40, 0x40, 0x40, 0x40, 0x3c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x38, 0x04, 0x02, 0x02, 0x3a, 0x46, 0x42, 0x42, 0x44,
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x40, 0x20, 0x20, 0x10, 0x10,
	0x10, 0x08, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42,
	0x24, 0x18, 0x24, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1c, 0x22, 0x42, 0x42, 0x62, 0x5c, 0x40, 0x40, 0x20, 0x1c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20,
	0x18, 0x04, 0x18, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x30, 0x40, 0x30, 0x08, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x40, 0x40, 0x30, 0x08, 0x08, 0x00,
	0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x22, 0x41, 0x59, 0x55,
	0x55, 0x55, 0x39, 0x01, 0x02, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14,
	0x14, 0x14, 0x14, 0x22, 0x3e, 0x22, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3e, 0x42, 0x42, 0x42, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x44,
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x22, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x22, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x02,
	0x02, 0x7e, 0x02, 0x02, 0x02, 0x02, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x7e, 0x02, 0x02, 0x02, 0x7e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x38, 0x44, 0x02, 0x02, 0x02, 0x72, 0x42, 0x42, 0x44, 0x38,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42,
	0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x1e, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x82, 0x42, 0x22, 0x12, 0x0a, 0x0e, 0x12, 0x22, 0x42, 0x82, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x66, 0x66, 0x5a, 0x5a,
	0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x46,
	0x46, 0x4a, 0x4a, 0x52, 0x52, 0x62, 0x62, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x3e, 0x42, 0x42, 0x3e, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x24, 0x18, 0x10, 0x60, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x42, 0x42,
	0x42, 0x3e, 0x12, 0x22, 0x22, 0x42, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3c, 0x42, 0x02, 0x02, 0x0c, 0x30, 0x40, 0x40, 0x42, 0x3c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22,
	0x22, 0x14, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41,
	0x41, 0x41, 0x49, 0x49, 0x55, 0x55, 0x55, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x14, 0x22, 0x22, 0x41, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x40, 0x20, 0x10, 0x10,
	0x08, 0x08, 0x04, 0x02, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x44, 0x44, 0x82, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
	0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x7c, 0x42, 0x62, 0x5c,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x1a, 0x26, 0x42, 0x42,
	0x42, 0x26, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78,
	0x04, 0x02, 0x02, 0x02, 0x04, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x40, 0x40, 0x58, 0x64, 0x42, 0x42, 0x42, 0x64, 0x58, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x7e, 0x02, 0x04, 0x78, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x08, 0x08, 0x7e, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x22,
	0x22, 0x22, 0x1c, 0x02, 0x3e, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x02, 0x02,
	0x02, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x00, 0x00, 0x1c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x1c, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x22, 0x12, 0x0a,
	0x0e, 0x12, 0x22, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x37, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 0x42,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42,
	0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a,
	0x26, 0x42, 0x42, 0x42, 0x26, 0x1a, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x58, 0x64, 0x42, 0x42, 0x42, 0x64, 0x58, 0x40, 0x40, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x02, 0x02, 0x3c, 0x40,
	0x40, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3c, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x62, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x41, 0x22, 0x22, 0x36, 0x14, 0x14, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x49, 0x55, 0x55, 0x22,
	0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x24, 0x18,
	0x18, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x41, 0x22, 0x22, 0x14, 0x14, 0x14, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7e, 0x20, 0x10, 0x08, 0x08, 0x04, 0x7e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x10, 0x10,
	0x10, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x8e, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const ui_font_t font_fixed_8x16 =
	{{8, 16}, font_fixed_8x16_glyph_data, 0x20, 95, (8 * 16 + 7U) >> 3};

static const uint8_t font_fixed_24x19_glyph_data[] = {
	0xe0, 0xff, 0x07, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0x3c, 0x00, 0x3c, 0x1c,
	0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00,
	0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38,
	0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x3c, 0xf8, 0xff, 0x1f, 0xf8,
	0xff, 0x1f, 0xe0, 0xff, 0x07, 0x00, 0x78, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x7e,
	0x00, 0x00, 0x7f, 0x00, 0x80, 0x77, 0x00, 0xc0, 0x73, 0x00, 0xc0, 0x71, 0x00,
	0xc0, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00,
	0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70,
	0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0xe0, 0xff, 0x07,
	0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0x3c, 0x00, 0x3c, 0x1c, 0x00, 0x38, 0x1c,
	0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x3c, 0x00, 0xfc,
	0x1f, 0xe0, 0xff, 0x1f, 0xf8, 0xff, 0x07, 0xfc, 0x07, 0x00, 0x3c, 0x00, 0x00,
	0x1c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xfc,
	0xff, 0x3f, 0xe0, 0xff, 0x07, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x3f, 0x3c, 0x00,
	0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38,
	0x00, 0xfe, 0x3f, 0x00, 0xfe, 0x1f, 0x00, 0xfe, 0x3f, 0x00, 0x00, 0x38, 0x00,
	0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x38, 0xf8, 0xff,
	0x3f, 0xf8, 0xff, 0x1f, 0xe0, 0xff, 0x07, 0x00, 0x80, 0x0f, 0x00, 0xc0, 0x0f,
	0x00, 0xe0, 0x0f, 0x00, 0xf8, 0x0f, 0x00, 0x7c, 0x0f, 0x00, 0x1e, 0x0f, 0x00,
	0x0f, 0x0f, 0xc0, 0x07, 0x0f, 0xe0, 0x01, 0x0f, 0xf0, 0x00, 0x0f, 0x7c, 0x00,
	0x0f, 0x1e, 0x00, 0x0f, 0xfe, 0xff, 0x7f, 0xfe, 0xff, 0x7f, 0xfe, 0xff, 0x7f,
	0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0xfc,
	0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0x1c, 0x00, 0x00, 0x1c, 0x00,
	0x00, 0x1c, 0x00, 0x00, 0xdc, 0xff, 0x07, 0xfc, 0xff, 0x1f, 0xfc, 0xff, 0x1f,
	0x3c, 0x00, 0x3c, 0x1c, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x1c,
	0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x3c, 0xf8, 0xff, 0x1f, 0xf8, 0xff,
	0x1f, 0xe0, 0xff, 0x07, 0xe0, 0xff, 0x07, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
	0x3c, 0x00, 0x3c, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x00, 0xdc,
	0xff, 0x07, 0xfc, 0xff, 0x1f, 0xfc, 0xff, 0x1f, 0x3c, 0x00, 0x3c, 0x1c, 0x00,
	0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x3c,
	0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xe0, 0xff, 0x07, 0xfc, 0xff, 0x7f, 0xfc,
	0xff, 0x7f, 0xfc, 0xff, 0x7f, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00,
	0x1e, 0x00, 0x00, 0x0f, 0x00, 0x80, 0x07, 0x00, 0xc0, 0x03, 0x00, 0xe0, 0x01,
	0x00, 0xf0, 0x01, 0x00, 0xf0, 0x00, 0x00, 0x78, 0x00, 0x00, 0x3c, 0x00, 0x00,
	0x1e, 0x00, 0x00, 0x0f, 0x00, 0x80, 0x0f, 0x00, 0x80, 0x07, 0x00, 0xc0, 0x03,
	0x00, 0xe0, 0xff, 0x07, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0x3c, 0x00, 0x3c,
	0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x3c, 0xf8,
	0xff, 0x1f, 0xf0, 0xff, 0x0f, 0xf8, 0xff, 0x1f, 0x3c, 0x00, 0x38, 0x1c, 0x00,
	0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x3c, 0xf8, 0xff, 0x1f,
	0xf8, 0xff, 0x1f, 0xe0, 0xff, 0x07, 0xe0, 0xff, 0x07, 0xf8, 0xff, 0x1f, 0xf8,
	0xff, 0x1f, 0x3c, 0x00, 0x3c, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00,
	0x38, 0x1c, 0x00, 0x38, 0x3c, 0x00, 0x3c, 0xf8, 0xff, 0x3f, 0xf8, 0xff, 0x3f,
	0xe0, 0xff, 0x3b, 0x00, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x1c, 0x00, 0x38, 0x3c,
	0x00, 0x3c, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xe0, 0xff, 0x07,
};

static const ui_font_t font_fixed_24x19 =
	{{24, 19}, font_fixed_24x19_glyph_data, 0x30, 10, (24 * 19 + 7U) >> 3};

static const uint8_t font_fixed_16x14_glyph_data[] = {
	0xf8, 0x1f, 0xfc, 0x3f, 0x0e, 0x70, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06,
	0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x0e, 0x70, 0xfc, 0x3f,
	0xf8, 0x1f, 0x00, 0x03, 0x80, 0x03, 0xc0, 0x03, 0xe0, 0x03, 0x70, 0x03, 0x20,
	0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03,
	0x00, 0x03, 0x00, 0x03, 0xf8, 0x1f, 0xfc, 0x3f, 0x0e, 0x70, 0x06, 0x60, 0x00,
	0x60, 0x00, 0x70, 0x80, 0x3f, 0xf8, 0x1f, 0xfc, 0x00, 0x0e, 0x00, 0x06, 0x00,
	0x06, 0x00, 0xfe, 0x7f, 0xfe, 0x7f, 0xf8, 0x1f, 0xfc, 0x3f, 0x0e, 0x70, 0x06,
	0x60, 0x00, 0x60, 0x00, 0x60, 0xc0, 0x3f, 0xc0, 0x7f, 0x00, 0x60, 0x00, 0x60,
	0x06, 0x60, 0x0e, 0x70, 0xfc, 0x3f, 0xf8, 0x1f, 0x00, 0x1c, 0x00, 0x1e, 0x00,
	0x1f, 0x80, 0x1b, 0xc0, 0x19, 0xe0, 0x18, 0x70, 0x18, 0x38, 0x18, 0x1c, 0x18,
	0xfe, 0x7f, 0xfe, 0x7f, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0xfe, 0x7f, 0xfe,
	0x7f, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0xf6, 0x1f, 0xfe, 0x3f, 0x0e, 0x70,
	0x00, 0x60, 0x00, 0x60, 0x06, 0x60, 0x0e, 0x70, 0xfc, 0x3f, 0xf8, 0x1f, 0xf8,
	0x1f, 0xfc, 0x3f, 0x0e, 0x70, 0x06, 0x60, 0x06, 0x00, 0xf6, 0x1f, 0xfe, 0x3f,
	0x0e, 0x70, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x0e, 0x70, 0xfc, 0x3f, 0xf8,
	0x1f, 0xfe, 0x7f, 0xfe, 0x7f, 0x00, 0x70, 0x00, 0x30, 0x00, 0x18, 0x00, 0x1c,
	0x00, 0x0c, 0x00, 0x06, 0x00, 0x07, 0x80, 0x03, 0x80, 0x01, 0xc0, 0x00, 0xe0,
	0x00, 0x60, 0x00, 0xf8, 0x1f, 0xfc, 0x3f, 0x0e, 0x70, 0x06, 0x60, 0x06, 0x60,
	0x0e, 0x70, 0xfc, 0x3f, 0xfc, 0x3f, 0x0e, 0x70, 0x06, 0x60, 0x06, 0x60, 0x0e,
	0x70, 0xfc, 0x3f, 0xf8, 0x1f, 0xf8, 0x1f, 0xfc, 0x3f, 0x0e, 0x70, 0x06, 0x60,
	0x06, 0x60, 0x06, 0x60, 0x0e, 0x70, 0xfc, 0x7f, 0xf8, 0x6f, 0x00, 0x60, 0x06,
	0x60, 0x0e, 0x70, 0xfc, 0x3f, 0xf8, 0x1f,
};

static const ui_font_t font_fixed_16x14 =
	{{16, 14}, font_fixed_16x14_glyph_data, 0x30, 10, (16 * 14 + 7U) >> 3};

static const uint8_t bitmap_amp_rx_data[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60,
	0x0c, 0x00, 0x30, 0x0c, 0x00, 0x30, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18,
	0x30, 0x00, 0x0c, 0x30, 0x00, 0x0c, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06,
	0xc0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0x80, 0x81, 0x01, 0x80, 0x81, 0x01,
	0x00, 0xc3, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x66, 0x00, 0x00, 0x66, 0x00,
	0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00};

static const ui_bitmap_t bitmap_amp_rx = {{24, 24}, bitmap_amp_rx_data};

static const uint8_t bitmap_amp_tx_data[] = {
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00,
	0x00, 0x66, 0x00, 0x00, 0x66, 0x00, 0x00, 0xc3, 0x00, 0x00, 0xc3, 0x00,
	0x80, 0x81, 0x01, 0x80, 0x81, 0x01, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x03,
	0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x30, 0x00, 0x0c, 0x30, 0x00, 0x0c,
	0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x0c, 0x00, 0x30, 0x0c, 0x00, 0x30,
	0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const ui_bitmap_t bitmap_amp_tx = {{24, 24}, bitmap_amp_tx_data};

static const uint8_t bitmap_antenna_data[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x18, 0x60, 0x06, 0x18, 0x60,
	0x0c, 0x18, 0x30, 0x0c, 0x18, 0x30, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
	0x30, 0x18, 0x0c, 0x30, 0x18, 0x0c, 0x60, 0x18, 0x06, 0x60, 0x18, 0x06,
	0xc0, 0x18, 0x03, 0xc0, 0x18, 0x03, 0x80, 0x99, 0x01, 0x80, 0x99, 0x01,
	0x00, 0xdb, 0x00, 0x00, 0xdb, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00,
	0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00};

static const ui_bitmap_t bitmap_antenna = {{24, 24}, bitmap_antenna_data};

static const uint8_t bitmap_filter_hp_data[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0,
	0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0, 0x03, 0xf8, 0xc7, 0x03, 0xfc, 0xc7,
	0x03, 0x0e, 0xc0, 0x03, 0x06, 0xc0, 0x03, 0x03, 0xc0, 0x03, 0x03, 0xc0,
	0x83, 0x01, 0xc0, 0x83, 0x01, 0xc0, 0xc3, 0x00, 0xc0, 0xc3, 0x00, 0xc0,
	0x63, 0x00, 0xc0, 0x63, 0x00, 0xc0, 0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0,
	0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const ui_bitmap_t bitmap_filter_hp = {{24, 24}, bitmap_filter_hp_data};

static const uint8_t bitmap_filter_lp_data[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0,
	0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0, 0xe3, 0x1f, 0xc0, 0xe3, 0x3f, 0xc0,
	0x03, 0x70, 0xc0, 0x03, 0x60, 0xc0, 0x03, 0xc0, 0xc0, 0x03, 0xc0, 0xc0,
	0x03, 0x80, 0xc1, 0x03, 0x80, 0xc1, 0x03, 0x00, 0xc3, 0x03, 0x00, 0xc3,
	0x03, 0x00, 0xc6, 0x03, 0x00, 0xc6, 0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0,
	0x03, 0x00, 0xc0, 0x03, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const ui_bitmap_t bitmap_filter_lp = {{24, 24}, bitmap_filter_lp_data};

static const uint8_t bitmap_mixer_data[] = {
	0x00, 0x7e, 0x00, 0xc0, 0xff, 0x03, 0xe0, 0x81, 0x07, 0x70, 0x00, 0x0e,
	0x38, 0x00, 0x1c, 0x7c, 0x00, 0x3e, 0xee, 0x00, 0x77, 0xc6, 0x81, 0x63,
	0x86, 0xc3, 0x61, 0x03, 0xe7, 0xc0, 0x03, 0x7e, 0xc0, 0x03, 0x3c, 0xc0,
	0x03, 0x3c, 0xc0, 0x03, 0x7e, 0xc0, 0x03, 0xe7, 0xc0, 0x86, 0xc3, 0x61,
	0xc6, 0x81, 0x63, 0xee, 0x00, 0x77, 0x7c, 0x00, 0x3e, 0x38, 0x00, 0x1c,
	0x70, 0x00, 0x0e, 0xe0, 0x81, 0x07, 0xc0, 0xff, 0x03, 0x00, 0x7e, 0x00};

static const ui_bitmap_t bitmap_mixer = {{24, 24}, bitmap_mixer_data};

static const uint8_t bitmap_oscillator_data[] = {
	0x00, 0x7e, 0x00, 0xc0, 0xff, 0x03, 0xe0, 0x81, 0x07, 0x70, 0x00, 0x0e,
	0x38, 0x00, 0x1c, 0x1c, 0x00, 0x38, 0x0e, 0x03, 0x70, 0x86, 0x07, 0x60,
	0xc6, 0x0f, 0x60, 0xc3, 0x0c, 0xc0, 0xe3, 0x1c, 0xc0, 0x63, 0x18, 0xc6,
	0x63, 0x18, 0xc6, 0x03, 0x38, 0xc7, 0x03, 0x30, 0xc3, 0x06, 0xf0, 0x63,
	0x06, 0xe0, 0x61, 0x0e, 0xc0, 0x70, 0x1c, 0x00, 0x38, 0x38, 0x00, 0x1c,
	0x70, 0x00, 0x0e, 0xe0, 0x81, 0x07, 0xc0, 0xff, 0x03, 0x00, 0x7e, 0x00};

static const ui_bitmap_t bitmap_oscillator = {{24, 24}, bitmap_oscillator_data};

static const uint8_t bitmap_wire_8_data[] = {0xff, 0xff};

static const ui_bitmap_t bitmap_wire_8 = {{2, 8}, bitmap_wire_8_data};

static const uint8_t bitmap_wire_24_data[] = {
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
	0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00};

static const ui_bitmap_t bitmap_wire_24 = {{24, 24}, bitmap_wire_24_data};

static const uint8_t bitmap_blank_24_data[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const ui_bitmap_t bitmap_blank_24 = {{24, 24}, bitmap_blank_24_data};

static const uint8_t bitmap_waves_rx_data[] = {
	0xc0, 0x00, 0x60, 0x00, 0x70, 0x06, 0x30, 0x07, 0x38, 0x03, 0x98, 0x33,
	0x98, 0x39, 0x98, 0x19, 0xcc, 0x18, 0xcc, 0x0c, 0xcc, 0x0c, 0xcc, 0x0c,
	0xcc, 0x0c, 0xcc, 0x0c, 0xcc, 0x0c, 0xcc, 0x18, 0x98, 0x19, 0x98, 0x39,
	0x98, 0x33, 0x38, 0x03, 0x30, 0x07, 0x70, 0x06, 0x60, 0x00, 0xc0, 0x00};

static const ui_bitmap_t bitmap_waves_rx = {{16, 24}, bitmap_waves_rx_data};

static const uint8_t bitmap_waves_tx_data[] = {
	0x00, 0x03, 0x00, 0x06, 0x60, 0x0e, 0xe0, 0x0c, 0xc0, 0x1c, 0xcc, 0x19,
	0x9c, 0x19, 0x98, 0x19, 0x18, 0x33, 0x30, 0x33, 0x30, 0x33, 0x30, 0x33,
	0x30, 0x33, 0x30, 0x33, 0x30, 0x33, 0x18, 0x33, 0x98, 0x19, 0x9c, 0x19,
	0xcc, 0x19, 0xc0, 0x1c, 0xe0, 0x0c, 0x60, 0x0e, 0x00, 0x06, 0x00, 0x03};

static const ui_bitmap_t bitmap_waves_tx = {{16, 24}, bitmap_waves_tx_data};

__attribute__((unused)) static ui_color_t portapack_color_rgb(
	const uint_fast8_t r,
	const uint_fast8_t g,
	const uint_fast8_t b)
{
	const ui_color_t result = {
		.v = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3)};
	return result;
}

static const ui_color_t color_background = {0x001f};
static const ui_color_t color_foreground = {0xffff};

static ui_point_t portapack_lcd_draw_int(
	const ui_point_t point,
	uint64_t value,
	size_t field_width)
{
	const ui_point_t point_done = {
		.x = point.x + font_fixed_8x16.glyph_size.width * field_width,
		.y = point.y};
	ui_point_t point_next = point_done;

	for (size_t i = 0; i < field_width; i++) {
		const char c = ((i == 0) || (value != 0)) ? ('0' + value % 10) : ' ';
		value /= 10;

		const ui_bitmap_t glyph = portapack_font_glyph(&font_fixed_8x16, c);
		point_next.x -= glyph.size.width;
		portapack_draw_bitmap(
			point_next,
			glyph,
			color_foreground,
			color_background);
	}

	return point_done;
}

static ui_point_t portapack_lcd_draw_string(ui_point_t point, const char* s)
{
	while (*s) {
		const char c = *(s++);
		const ui_bitmap_t glyph = portapack_font_glyph(&font_fixed_8x16, c);
		portapack_draw_bitmap(point, glyph, color_foreground, color_background);
		point.x += glyph.size.width;
	}

	return point;
}

typedef struct draw_list_t {
	const ui_bitmap_t* bitmap;
	const ui_point_t point;
} draw_list_t;

static draw_list_t radio_draw_list[] = {
	{&bitmap_antenna, {32, 64}},
	{&bitmap_wire_8, {43, 88}},
	{&bitmap_wire_24, {32, 96}},
	{&bitmap_wire_8, {43, 120}},
	{&bitmap_filter_hp, {32, 128}},
	{&bitmap_wire_8, {43, 152}},
	{&bitmap_mixer, {32, 160}},
	{&bitmap_wire_8, {43, 184}},
	{&bitmap_amp_rx, {32, 192}},
	{&bitmap_wire_8, {43, 216}},
	{&bitmap_mixer, {32, 224}},
	{&bitmap_wire_8, {43, 248}},
	{&bitmap_filter_lp, {32, 256}},
	{&bitmap_wire_8, {43, 280}},
	{&bitmap_amp_rx, {32, 288}},
	{&bitmap_wire_8, {43, 312}},
	{&bitmap_oscillator, {208, 288}},
	{&bitmap_blank_24, {60, 60}},
};

typedef enum {
	RADIO_DRAW_LIST_ITEM_ANTENNA = 0,
	RADIO_DRAW_LIST_ITEM_RF_AMP = 2,
	RADIO_DRAW_LIST_ITEM_IMAGE_FILTER = 4,
	RADIO_DRAW_LIST_ITEM_RF_MIXER = 6,
	RADIO_DRAW_LIST_ITEM_BB_LNA_AMP = 8,
	RADIO_DRAW_LIST_ITEM_BB_MIXER = 10,
	RADIO_DRAW_LIST_ITEM_BB_FILTER = 12,
	RADIO_DRAW_LIST_ITEM_BB_VGA_AMP = 14,
	RADIO_DRAW_LIST_ITEM_CLOCK = 16,
	RADIO_DRAW_LIST_ITEM_WAVES = 17,
} radio_draw_list_item_t;

static ui_point_t portapack_ui_label_point(const radio_draw_list_item_t item)
{
	const uint8_t VALUES_X = 72;
	ui_point_t point = {VALUES_X, radio_draw_list[item].point.y + 4};
	return point;
}

static ui_point_t portapack_ui_draw_string(
	const radio_draw_list_item_t item,
	const char* s)
{
	return portapack_lcd_draw_string(portapack_ui_label_point(item), s);
}

static ui_point_t portapack_ui_draw_db(
	const radio_draw_list_item_t item,
	const uint32_t db)
{
	ui_point_t point = portapack_ui_label_point(item);
	point = portapack_lcd_draw_int(point, db, 2);
	return portapack_lcd_draw_string(point, " dB");
}

static ui_point_t portapack_ui_draw_bw_mhz(
	const radio_draw_list_item_t item,
	const uint64_t hz)
{
	const uint32_t lsd = 1000000 / 100;
	const uint32_t round_offset = lsd / 2;

	const uint64_t hz_offset = hz + round_offset;
	const uint32_t mhz = hz_offset / 1000000;
	const uint32_t frac = hz_offset / lsd;

	ui_point_t point = portapack_ui_label_point(item);
	point = portapack_lcd_draw_int(point, mhz, 2);
	point = portapack_lcd_draw_string(point, ".");
	point = portapack_lcd_draw_int(point, frac, 2);
	return portapack_lcd_draw_string(point, " MHz");
}

static void portapack_draw_radio_path_item(const radio_draw_list_item_t item)
{
	portapack_draw_bitmap(
		radio_draw_list[item].point,
		*radio_draw_list[item].bitmap,
		color_foreground,
		color_background);
}

static void portapack_radio_path_item_update(
	const radio_draw_list_item_t item,
	const ui_bitmap_t* const bitmap)
{
	if (bitmap != radio_draw_list[item].bitmap) {
		radio_draw_list[item].bitmap = bitmap;
		portapack_draw_radio_path_item(item);
	}
}

static rf_path_direction_t portapack_direction = RF_PATH_DIRECTION_OFF;
static bool portapack_lna_on = false;

static void portapack_radio_path_redraw()
{
	for (size_t i = 0; i < ARRAY_SIZEOF(radio_draw_list); i++) {
		portapack_draw_radio_path_item(i);
	}
}

static void portapack_ui_init(void)
{
	portapack_clear_display(color_background);
	portapack_backlight(true);
	portapack_radio_path_redraw();
}

static void portapack_ui_deinit(void)
{
	portapack_clear_display(color_background);
	portapack_backlight(false);
}

static void portapack_ui_set_frequency(uint64_t frequency)
{
	static char last[10] = "          ";

	ui_point_t point = {240 - 20, 16};

	uint64_t value = frequency;
	char s[10];
	for (int i = 0; i < 10; i++) {
		const char c = '0' + value % 10;
		s[i] = ((i >= 6) && (value == 0)) ? ' ' : c;
		value /= 10;
	}

	for (int i = 0; i < 10; i++) {
		const char c = s[i];

		const ui_font_t* const font =
			(i > 5) ? &font_fixed_24x19 : &font_fixed_16x14;
		point.x -= font->glyph_size.width;
		if ((i == 3) || (i == 6) || (i == 9)) {
			point.x -= 4;
		}

		if (c != last[i]) {
			const ui_bitmap_t glyph = portapack_font_glyph(font, c);

			if (c == ' ') {
				/* Blank out leading zeros. */
				const ui_rect_t rect = {point, glyph.size};
				portapack_fill_rectangle(rect, color_background);
			} else {
				portapack_draw_bitmap(
					point,
					glyph,
					color_foreground,
					color_background);
			}
			last[i] = c;
		}
	}
}

static void portapack_ui_set_sample_rate(uint32_t sample_rate)
{
#if 0
	ui_point_t point = { VALUES_X, 320 - 1 * 16 };
	portapack_lcd_draw_int(point, sample_rate, 8);
#else
	(void) sample_rate;
#endif
}

static void portapack_ui_set_direction(const rf_path_direction_t direction)
{
	switch (direction) {
	case RF_PATH_DIRECTION_TX:
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_WAVES,
			&bitmap_waves_tx);
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_RF_AMP,
			portapack_lna_on ? &bitmap_amp_tx : &bitmap_wire_24);
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_BB_LNA_AMP,
			&bitmap_amp_tx);
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_BB_VGA_AMP,
			&bitmap_wire_24);
		portapack_ui_draw_string(RADIO_DRAW_LIST_ITEM_BB_VGA_AMP, "     ");
		break;

	case RF_PATH_DIRECTION_RX:
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_WAVES,
			&bitmap_waves_rx);
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_RF_AMP,
			portapack_lna_on ? &bitmap_amp_rx : &bitmap_wire_24);
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_BB_LNA_AMP,
			&bitmap_amp_rx);
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_BB_VGA_AMP,
			&bitmap_amp_rx);
		break;

	case RF_PATH_DIRECTION_OFF:
	default:
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_WAVES,
			&bitmap_blank_24);
		break;
	}

	portapack_direction = direction;
}

static void portapack_ui_set_filter_bw(uint32_t bandwidth)
{
	portapack_ui_draw_bw_mhz(RADIO_DRAW_LIST_ITEM_BB_FILTER, bandwidth);
}

static void portapack_ui_set_lna_power(bool lna_on)
{
	portapack_lna_on = lna_on;
	portapack_radio_path_item_update(
		RADIO_DRAW_LIST_ITEM_RF_AMP,
		lna_on ?
			((portapack_direction == RF_PATH_DIRECTION_TX) ? &bitmap_amp_tx :
									 &bitmap_amp_rx) :
			&bitmap_wire_24);
	const char* const label = lna_on ? "14 dB" : "     ";
	portapack_ui_draw_string(RADIO_DRAW_LIST_ITEM_RF_AMP, label);
}

static void portapack_ui_set_bb_lna_gain(const uint32_t gain_db)
{
	portapack_ui_draw_db(RADIO_DRAW_LIST_ITEM_BB_LNA_AMP, gain_db);
}

static void portapack_ui_set_bb_vga_gain(const uint32_t gain_db)
{
	portapack_ui_draw_db(RADIO_DRAW_LIST_ITEM_BB_VGA_AMP, gain_db);
}

static void portapack_ui_set_bb_tx_vga_gain(const uint32_t gain_db)
{
	/* TODO: This function (and code throughout the HackRF project) is mis-labeled?
	 * According to the MAX2837 datasheet diagram, there is no baseband gain in the TX path.
	 * This gets called when the TX IF gain is changed.
	 */
	portapack_ui_draw_db(RADIO_DRAW_LIST_ITEM_BB_LNA_AMP, gain_db);
}

static void portapack_ui_set_first_if_frequency(const uint64_t frequency)
{
	(void) frequency;
}

static void portapack_ui_set_filter(const rf_path_filter_t filter)
{
	portapack_radio_path_item_update(
		RADIO_DRAW_LIST_ITEM_RF_MIXER,
		(filter == RF_PATH_FILTER_BYPASS) ? &bitmap_wire_24 : &bitmap_mixer);

	switch (filter) {
	default:
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_IMAGE_FILTER,
			&bitmap_wire_24);
		break;

	case RF_PATH_FILTER_LOW_PASS:
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_IMAGE_FILTER,
			&bitmap_filter_lp);
		break;

	case RF_PATH_FILTER_HIGH_PASS:
		portapack_radio_path_item_update(
			RADIO_DRAW_LIST_ITEM_IMAGE_FILTER,
			&bitmap_filter_hp);
		break;
	}
}

static void portapack_ui_set_antenna_bias(bool antenna_bias)
{
	(void) antenna_bias;
}

static void portapack_ui_set_clock_source(clock_source_t source)
{
	ui_point_t label_point = radio_draw_list[RADIO_DRAW_LIST_ITEM_CLOCK].point;
	label_point.x -= 0;
	label_point.y -= 16;

	const char* s = "HRF";
	switch (source) {
	case CLOCK_SOURCE_EXTERNAL: {
		s = "EXT";
		break;
	}
	case CLOCK_SOURCE_PORTAPACK: {
		s = "PPK";
		break;
	}
	default:
	case CLOCK_SOURCE_HACKRF: {
		s = "HRF";
		break;
	}
	}

	portapack_lcd_draw_string(label_point, s);
}

static void portapack_ui_set_transceiver_mode(transceiver_mode_t mode)
{
	(void) mode;
}

static bool portapack_ui_operacake_gpio_compatible(void)
{
	return false;
}

const hackrf_ui_t portapack_hackrf_ui = {
	&portapack_ui_init,
	&portapack_ui_deinit,
	&portapack_ui_set_frequency,
	&portapack_ui_set_sample_rate,
	&portapack_ui_set_direction,
	&portapack_ui_set_filter_bw,
	&portapack_ui_set_lna_power,
	&portapack_ui_set_bb_lna_gain,
	&portapack_ui_set_bb_vga_gain,
	&portapack_ui_set_bb_tx_vga_gain,
	&portapack_ui_set_first_if_frequency,
	&portapack_ui_set_filter,
	&portapack_ui_set_antenna_bias,
	&portapack_ui_set_clock_source,
	&portapack_ui_set_transceiver_mode,
	&portapack_ui_operacake_gpio_compatible,
};

const hackrf_ui_t* portapack_hackrf_ui_init()
{
	if (portapack()) {
		return &portapack_hackrf_ui;
	} else {
		return NULL;
	}
}
