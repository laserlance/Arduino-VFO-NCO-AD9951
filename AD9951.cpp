/* AD9951 Arduino library Version: 1.0.0B B means Beta not feta
 * Copyright (c) 2014 by Laser-Lance Fordham <Lance.Fordham@gmail.com>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
#include "AD9951.h"

#define cfr1_reg 0x00
#define cfr2_reg 0x01
#define asf_reg 0x02
#define arr_reg 0x03
#define ftw_reg 0x04
#define pow_reg 0x05
#define read_reg 0x00
#define write_reg 0x01


AD9951::AD9951(int ss_pin, int o_reset, int io_update, int clk_mode_sel, int pwr_dwn_ctrl, int o_s_k, int io_sync){

	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV32);

	sspin = ss_pin;
	oreset = o_reset;
	ioupdate = io_update;
	clkmodesel = clk_mode_sel;
	pwrdwnctrl = pwr_dwn_ctrl;
	osk = o_s_k;
	iosync = io_sync;

	if(sspin != SS){

		digitalWrite(sspin,HIGH);   //Put selceted SS high

		pinMode(sspin, OUTPUT);	    //Set pin as output

	}
	//Put some default value into the config vars
	//if these are not changed by user, then they
	//will be written when the config method is called

	AD9951::cfr1[0] = 0x02;
	AD9951::cfr1[1] = 0x02;
	AD9951::cfr1[2] = 0x00;
	AD9951::cfr1[3] = 0x07;
	AD9951::cfr2[0] = 0x00;
	AD9951::cfr2[1] = 0x00;
	AD9951::cfr2[2] = 0x18;
	AD9951::asf[0] = 0xff;
	AD9951::asf[1] = 0x3f;
	AD9951::arr = 0xff;
	AD9951::ftw[0] = 0x33;
	AD9951::ftw[1] = 0x00;
	AD9951::ftw[2] = 0x00;
	AD9951::ftw[3] = 0x00;
	AD9951::pow[0] = 0x00;
	AD9951::pow[1] = 0x00;


}

void AD9951::Config(){

	SendReg(cfr1_reg,write_reg);

	SendReg(cfr2_reg,write_reg);

	SendReg(asf_reg,write_reg);

	SendReg(arr_reg,write_reg);

	SendReg(ftw_reg,write_reg);

	SendReg(pow_reg,write_reg);

}

void AD9951::ChangeASF(word ASF){

	AD9951::asf[0] = ASF & 0xFF;
	AD9951::asf[1] = (ASF >> 8);

	SendReg(asf_reg,write_reg);

}
void AD9951::ChangeARR(int ARR){

	AD9951::arr = ARR;

	SendReg(arr_reg,write_reg);

}
void AD9951::ChangePhase(int degrees){

	//Need to convert degrees to a Phase Offset Word [POW]:
	// Formula:
	//
	// phase-offset = (pow/2^14) * 360-degrees
	//
	// Therefore:
	// pow = (phase-offset * 2^14) / 360
	//

	word poww = ((constrain(degrees,-360,360)) * 16384) / 360;

	AD9951::pow[0] = poww & 0xFF;
	AD9951::pow[1] = (poww >> 8);

	SendReg(pow_reg,write_reg);

}
void AD9951::toggleIOUpdate(){

     digitalWrite(ioupdate, HIGH);
	 delayMicroseconds(10);
     digitalWrite(ioupdate, LOW);

}
void AD9951::toggleIOSync(){

     digitalWrite(iosync, HIGH);
	 delayMicroseconds(10);
     digitalWrite(iosync, LOW);

}

void AD9951::toggleReset(){

	digitalWrite(oreset, HIGH);
	delayMicroseconds(10);
	digitalWrite(oreset, LOW);

}

void AD9951::SendReg(byte reg, byte read_write){

	int i;
	byte rw;
	byte buf[4];

	if(read_write == write_reg){

		rw = 0x00; // it's a write instruction

	}else if(read_write == read_reg){

		rw = 0x80; // it's a read instruction
	}

	digitalWrite(sspin,LOW);

	switch(reg){

		case cfr1_reg: //configuration 1 register

			reg = rw | cfr1_reg; //combine the read-write instruction with the register address

			SPI.transfer(reg); //send the instruction byte first

			//The timing diagram in the datasheet shows a pause here, but I don't know if that's real
			//I could not find any documentation that says a delay should exist, or by how much.

			for (i = 3; i>= 0; i--){ //MSB first

				buf[i] = SPI.transfer (AD9951::cfr1[i]); //send the data byte(s)

			}

			if(read_write == read_reg){ //if this was a read instruction, move the contents of buffer to register

				AD9951::cfr1[3] = buf[3];
				AD9951::cfr1[2] = buf[2];
				AD9951::cfr1[1] = buf[1];
				AD9951::cfr1[0] = buf[0];
			}

		break;

		case cfr2_reg:

			reg = rw | cfr2_reg;

			SPI.transfer(reg);

			for (i = 2; i>= 0; i--){ //MSB first

				buf[i] = SPI.transfer (AD9951::cfr2[i]);

			}

			if(read_write == read_reg){

				AD9951::cfr2[2] = buf[2];
				AD9951::cfr2[1] = buf[1];
				AD9951::cfr2[0] = buf[0];
			}

		break;

		case asf_reg:

			reg = rw | asf_reg;

			SPI.transfer(reg);

			for (i = 1; i>= 0; i--){ //MSB first

				buf[i] = SPI.transfer (AD9951::asf[i]);

			}

			if(read_write == read_reg){

				AD9951::asf[1] = buf[1];
				AD9951::asf[0] = buf[0];
			}

		break;

		case arr_reg:

			reg = rw | arr_reg;

			SPI.transfer(reg);

			buf[0] = SPI.transfer (AD9951::arr);

			if(read_write == read_reg){

				AD9951::arr = buf[0];
			}

		break;

		case ftw_reg:

			reg = rw | ftw_reg;

			SPI.transfer(reg);

			for (i = 3; i>= 0; i--){ //MSB first

				buf[i] = SPI.transfer (AD9951::ftw[i]);


			}

			if(read_write == read_reg){

				AD9951::ftw[3] = buf[3];
				AD9951::ftw[2] = buf[2];
				AD9951::ftw[1] = buf[1];
				AD9951::ftw[0] = buf[0];
			}

		break;

		case pow_reg:

			reg = rw | pow_reg;

			SPI.transfer(reg);

			for (i = 1; i>= 0; i--){ //MSB first

				buf[i] = SPI.transfer (AD9951::pow[i]);

			}

			if(read_write == read_reg){

				AD9951::pow[1] = buf[1];
				AD9951::pow[0] = buf[0];
			}

		break;
	}

	digitalWrite(sspin,HIGH);

	AD9951::toggleIOSync();
	AD9951::toggleIOUpdate();

}
