/* AD9951 Arduino library Version: 1.0.0B B means Beta not feta
 * Copyright (c) 2014 by Laser-Lance Fordham <Lance.Fordham@gmail.com>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef AD9951_h
#define AD9951_h

#include "Arduino.h"
#include <SPI.h>
#include "pins_arduino.h"

class AD9951{

		public:

			AD9951(int ss_pin, int o_reset, int io_update, int clk_mode_sel, int pwr_dwn_ctrl, int o_s_k, int io_sync);
			void Config();
			void SendReg(byte reg, byte read_write);
			void ChangePhase(int degrees);
			void ChangeASF(word ASF);
			void ChangeARR(int ARR);
			void toggleIOUpdate();
			void toggleIOSync();
			void toggleReset();
			byte cfr1[4];
			byte cfr2[3];
			byte asf[2];
			byte arr;
			byte ftw[4];
			byte pow[2];

		private:

			int sspin;
			int oreset;
			int ioupdate;
			int clkmodesel;
			int pwrdwnctrl;
			int osk;
			int iosync;

};

#endif

