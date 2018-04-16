/* AD9951 Arduino library Version: 1.0.0B B means Beta not feta
 * Copyright (c) 2014 by Laser-Lance Fordham <Lance.Fordham@gmail.com>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
 
#include <SPI.h> //Must include this since the Arduino talks to the AD9951 via the SPI
#include <AD9951.h>

//I don't know why, but even though these are defined in the library, I had to re-define them here to use them here
#define cfr1_reg 0x00
#define cfr2_reg 0x01
#define asf_reg 0x02
#define arr_reg 0x03
#define ftw_reg 0x04
#define pow_reg 0x05
#define read_reg 0x00
#define write_reg 0x01

const unsigned int oreset = 43;
const unsigned int ioupdate = 11;
const unsigned int clkmodesel = 12;
const unsigned int pwrdwnctrl = 45;
const unsigned int osk = 10;
const unsigned int iosync = 42;
const unsigned int cs = 41;

const unsigned int serial1_baud = 9600;
boolean debugcom = true;


AD9951 VFO(cs, oreset, ioupdate, clkmodesel, pwrdwnctrl, osk, iosync); 

void setup() {

     Serial.begin(serial1_baud); //PC port
     
     pinMode(oreset, OUTPUT); //RESET
     digitalWrite(oreset, LOW);
     
     pinMode(ioupdate, OUTPUT); //IO_UPDATE
     digitalWrite(ioupdate, LOW);
     
     pinMode(clkmodesel, OUTPUT); //CLKMODESEL
     digitalWrite(clkmodesel, LOW);
     
     pinMode(pwrdwnctrl, OUTPUT); //PWRDWNCTRL
     digitalWrite(pwrdwnctrl, LOW);
     
     pinMode(osk, OUTPUT); //OSK
     digitalWrite(osk, LOW);
     
      pinMode(osk, OUTPUT); //OSK Default this to be "ON"
     digitalWrite(osk, HIGH);
     
     pinMode(iosync, OUTPUT); //IOSYNC
     digitalWrite(iosync, LOW);
     
     VFO.toggleReset();
     VFO.toggleIOSync();
     
     //These are all of the registers that can be changed.
     //Set the value of each register and then call the Config method
     //See page 14 of the fancy datasheet for information on the registers
     VFO.cfr1[0] = 0x00;
     VFO.cfr1[1] = 0x02;
     VFO.cfr1[2] = 0x00;
     VFO.cfr1[3] = 0x07;
     VFO.SendReg(cfr1_reg,write_reg);
     
     VFO.cfr2[0] = 0x00;
     VFO.cfr2[1] = 0x00;
     VFO.cfr2[2] = 0x18;
     VFO.SendReg(cfr2_reg,write_reg);
     
     VFO.asf[0] = 0xff;
     VFO.asf[1] = 0x3f;
     VFO.SendReg(asf_reg,write_reg);
     
     VFO.arr = 0xff;
     VFO.SendReg(arr_reg,write_reg);
     
     VFO.ftw[0] = 0x00;
     VFO.ftw[1] = 0x00;
     VFO.ftw[2] = 0x00;
     VFO.ftw[3] = 0x00;
     VFO.SendReg(ftw_reg,write_reg);
     
     VFO.pow[0] = 0x00;
     VFO.pow[1] = 0x00;
     VFO.SendReg(pow_reg,write_reg);

     
     
     //VFO.Config(); //must call this or the default values will be used which may not work for your application 
     
     //When you want to change a register, you can do so the following way:
     //To change frequency:
     // 10KHz
     /*
     VFO.ftw[0] = 0x6e;
     VFO.ftw[1] = 0xa3;
     VFO.ftw[2] = 0x01;
     VFO.ftw[3] = 0x00;
     */
     // 100KHz
     VFO.ftw[0] = 0x4E;
     VFO.ftw[1] = 0x62;
     VFO.ftw[2] = 0x10;
     VFO.ftw[3] = 0x00;
     
     //27MHz
     VFO.ftw[0] = 0x14;
     VFO.ftw[1] = 0xAE;
     VFO.ftw[2] = 0x47;
     VFO.ftw[3] = 0x11;
     
     //41MHz
     VFO.ftw[0] = 0xA4;
     VFO.ftw[1] = 0x70;
     VFO.ftw[2] = 0x3D;
     VFO.ftw[3] = 0x1A;
     
     //24MHz
     VFO.ftw[0] = 0xF6;
     VFO.ftw[1] = 0x28;
     VFO.ftw[2] = 0x5C;
     VFO.ftw[3] = 0x0F;
     
     //80MHz
     VFO.ftw[0] = 0x33;
     VFO.ftw[1] = 0x33;
     VFO.ftw[2] = 0x33;
     VFO.ftw[3] = 0x33;
     
     //255KHz
     /*
     VFO.ftw[0] = 0x7A;
     VFO.ftw[1] = 0xC7;
     VFO.ftw[2] = 0x29;
     VFO.ftw[3] = 0x00;
     */
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     
     //Note: you can change just one byte of the FTW register, but all three bytes are required to be sent, which the library handles
     //In the future, the library will have a method that allows one to give it a frequency, or a frequency offset, 
     //so that the frequency word is automagically calculated. This is just a rudimentary library at the moment.
     
}

void loop() {
     
}



