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

import socket
import json
import os
import contextlib
import datetime

class Recorder():
	def __init__(self, args):
		self._args = args
		with open(self._args.config) as f:
			self._config = json.load(f)
		with contextlib.suppress(FileExistsError):
			os.makedirs(self._config["logdir"])
		self._average = [ ]

	def _received_datapoint(self, data_point):
		hr = data_point["last_value"]
		self._average.append(hr)
		if len(self._average) > 60:
			self._average = self._average[-60 : ]
		average_hr = sum(self._average) / len(self._average)

		stars = round(hr / 2)
		if hr < 120:
			color = "\x1b[32m"
		elif hr < 155:
			color = "\x1b[33m"
		else:
			color = "\x1b[31m"
		color_off = "\x1b[0m"
		print("%3d (avg %3.0f): %s%s%s" % (hr, average_hr, color, "*" * stars, color_off))

	def _log_to(self, logfile):
		sockfile = self._socket.makefile()
		while True:
			line = sockfile.readline()
			data_point = json.loads(line)
			if data_point["connected"]:
				self._received_datapoint(data_point)
				print("%.6f %d" % (data_point["ts"], data_point["last_value"]), file = logfile)

	def run(self):
		self._socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
		self._socket.connect(self._config["socket"])

		logfile_name = self._config["logdir"] + "/heartrate_" + datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S") + ".txt"
		with open(logfile_name, "w") as f:
			self._log_to(f)
