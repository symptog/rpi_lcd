/*
 * rpii2c.h
 * 
 * Created by Tobias Gall <toga@tu-chemnitz.eu>
 * Based on Adafruit's python code for CharLCDPlate
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


#ifndef RPII2C_h
#define RPII2C_h

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include "smbus.c" 

int fd;

void rpiI2cSetup(__u8, __u8);
void rpiI2cWrite(__u8, __u8);
void rpiI2cClose(void);
__u8 rpiI2cRead8(__u8);
__u16 rpiI2cRead16(__u8);

#endif
