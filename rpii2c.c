/*
 * rpii2c.c
 * 
 * Copyright 2013 Tobias Gall <toga@tu-chemnitz.eu>
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


#include "rpii2c.h"

int fd;

void rpiI2cSetup(__u8 adr, __u8 busnum)
{
	
	char *fileName;
	
	if(busnum == 0)
		fileName = "/dev/i2c-0";
	else if(busnum == 1)
		fileName = "/dev/i2c-1";
	else 
		exit(1);
		 
	if((fd = open(fileName, O_RDWR)) < 0)
		exit(1);
   
	if(ioctl(fd, I2C_SLAVE, adr) < 0) {               
		close(fd);
		exit(1);
	}	
}

void rpiI2cWrite(__u8 reg, __u8 value)
{
	if (i2c_smbus_write_byte_data(fd, reg, value) < 0) {
		close(fd);
		exit(1);
	}
}

void rpiI2cClose(void)
{
	close(fd);
}

__u8 rpiI2cRead8(__u8 reg)
{
	__u8 res = i2c_smbus_read_byte_data(fd, reg);
	
	return res;
}

__u16 rpiI2cRead16(__u8 reg)
{
	
	__u16 hi = i2c_smbus_read_byte_data(fd, reg);
	__u16 res = (hi << 8) + i2c_smbus_read_byte_data(fd, reg+1);
	
	return res;
}


