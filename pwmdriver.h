/*
 * pwmdriver.h
 * 
 * Created by Tobias Gall <toga@tu-chemnitz.eu>
 * Based on Adafruit's python code for PCA9685 16-Channel PWM Servo Driver
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef PWMDRIVER_h
#define PWMDRIVER_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <linux/types.h>

#include "rpii2c.c"

#define SUBADR1			0x02
#define SUBADR2			0x03
#define SUBADR3			0x04
#define MODE1			0x00
#define PRESCALE		0xFE
#define LED0_ON_L		0x06
#define LED0_ON_H		0x07
#define LED0_OFF_L		0x08
#define LED0_OFF_H		0x09
#define LED1_ON_L		0x0A
#define LED1_ON_H		0x0B
#define LED1_OFF_L		0x0C
#define LED1_OFF_H		0x0D
#define ALLLED_ON_L		0xFA
#define ALLLED_ON_H		0xFB
#define ALLLED_OFF_L	0xFC
#define ALLLED_OFF_H	0xFD

void pwmSetup(__u8, __u8);
void pwmSetPWMFreq(__u8);
void pwmSetPWM(__u8, __s16, __s16);
void servosSetup();
void servosSetSpeeds(__s16, __s16);

#endif
