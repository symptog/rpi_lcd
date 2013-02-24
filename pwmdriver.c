/*
 * pwmdriver.c
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

#include <math.h>

#include "pwmdriver.h"

void pwmSetup(__u8 addr, __u8 busnum)
{
	rpiI2cSetup(addr, busnum);
	rpiI2cWrite(MODE1, 0x00);
}

void pwmSetPWMFreq(float_t freq)
{
	float_t prescaleval = 25000000.0;
	prescaleval /= 4096.0;
	prescaleval /= freq;
	prescaleval -= 1.0;
	float_t prescale;
	prescale = floorf(prescaleval + 0.5);
	
	__u8 oldmode = rpiI2cRead8(MODE1);
	__u8 newmode = (oldmode & 0x7F) | 0x10;
	
	rpiI2cWrite(MODE1, newmode);
	__u8 pre_scale = floorf(prescale);
	rpiI2cWrite(PRESCALE, pre_scale);
	rpiI2cWrite(MODE1, oldmode);
	usleep(500);
	rpiI2cWrite(MODE1, oldmode | 0x80);
}

void pwmSetPWM(__u8 channel, __s16 on, __s16 off)
{
	rpiI2cWrite(LED0_ON_L+4*channel, on & 0xFF);
	rpiI2cWrite(LED0_ON_H+4*channel, on >> 8);
	rpiI2cWrite(LED0_OFF_L+4*channel, off & 0xFF);
	rpiI2cWrite(LED0_OFF_H+4*channel, off >> 8);
}

void servosSetup()
{
	rpiI2cWrite(LED0_ON_L, 0x00);
	rpiI2cWrite(LED0_ON_H, 0x00);
	rpiI2cWrite(LED1_ON_L, 0x00);
	rpiI2cWrite(LED1_ON_H, 0x00);
}

void servosSetSpeeds(__s16 left, __s16 right)
{
	right = -right;
	
	if(left >= 5 && left <= 5)
		left = 0;
	else if(left < -100)
		left = 400-200;
	else if(left >= 100)
		left = 400+200;
	else
		left = 400 + (left*2);
	
	if(right >= 5 && right <= 5)
		right = 0;
	else if(right < -100)
		right = 404-200;
	else if(right >= 100)
		right = 404+200;
	else
		right = 404 + (right*2);

	rpiI2cWrite(LED0_OFF_L, left);
	rpiI2cWrite(LED0_OFF_H, left >> 8);
	rpiI2cWrite(LED1_OFF_L, right);
	rpiI2cWrite(LED1_OFF_H, right >> 8);
}
