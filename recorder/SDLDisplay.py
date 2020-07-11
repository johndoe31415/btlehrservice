#	btlehrservice - Bluetooth-Low-Energy heart rate service
#	Copyright (C) 2020-2020 Johannes Bauer
#
#	This file is part of btlehrservice.
#
#	btlehrservice is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; this program is ONLY licensed under
#	version 3 of the License, later versions are explicitly excluded.
#
#	btlehrservice is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with btlehrservice; if not, write to the Free Software
#	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#	Johannes Bauer <JohannesBauer@gmx.de>

import cairo
import sdl2.ext

class SDLDisplay():
	def __init__(self, width, height):
		self._width = width
		self._height = height
		self._scale = width / 1920
		sdl2.ext.init()
		self._window = sdl2.ext.Window("Heartrate Monitor", size = (self._width, self._height))
		self._window.show()
		self._renderer = sdl2.ext.Renderer(self._window)
		self._font = sdl2.ext.FontManager("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf", size = 28)
		self._sprites = sdl2.ext.SpriteFactory(renderer = self._renderer)

		self._surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
		self._cctx = cairo.Context(self._surface)

	def _draw_text(self, text, x, y, font_size = 24):
		x = round(x / 16 * self._width)
		y = round(y / 9 * self._height)
		rendered = self._sprites.from_text(text, size = round(font_size * self._scale), fontmanager = self._font)
		self._renderer.copy(rendered, dstrect = (x, y, rendered.size[0], rendered.size[1]))

	def update(self, heartrate):
#		self._renderer.clear(sdl2.ext.Color(6, 5, 40))
#		self._renderer.draw_point((10, 10), sdl2.ext.Color(255, 0, 0))
#		avg_heartrate = 123
#		self._draw_text("♡  %d" % (heartrate), 0.5, 0.5, font_size = 64)
#		self._draw_text("Avg  %d" % (avg_heartrate), 4.5, 0.5, font_size = 64)
#		self._renderer.draw_rect((0, 0, 121, 111), color = sdl2.ext.Color(255, 255, 255))

		print(self._surface.get_data())
		rmask = 0xff << 24
		gmask = 0xff << 16
		bmask = 0xff << 8
		sdl_surface = sdl2.surface.SDL_CreateRGBSurfaceFrom(self._surface.get_data(), self._width, self._height, 32, 4 * self._width, rmask, gmask, bmask, 0)

		self._renderer.copy(self._surface)
		self._renderer.present()

if __name__ == "__main__":
	import time
	scale = 0.5
	display = SDLDisplay(round(scale * 1920), round(scale * 1080))
	hr = 120
	while True:
		display.update(hr)
		hr += 1
		time.sleep(1)
