/*
 * rpii2c.c
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


#include "rpii2c.h"

int fd; // FileDiscriptor

/*
 * 
 * name: rpiI2cSetup
 * @param __u8 addr (Address of I2C Device), __u8 busnum
 * @return void
 * 
 * Sets up an I2C Device
 * 
 */
void rpiI2cSetup(__u8 addr, __u8 busnum)
{
	
	char *fileName;
	
	if(busnum == 0)
		fileName = "/dev/i2c-0";
	else if(busnum == 1)
		fileName = "/dev/i2c-1";
	else 
		exit(1);
	// Open File for READ/WRITE
	if((fd = open(fileName, O_RDWR)) < 0)
		exit(1);
	// Sets Device as I2C Slave
	if(ioctl(fd, I2C_SLAVE, addr) < 0) {               
		close(fd);
		exit(1);
	}	
}

/*
 * 
 * name: rpiI2cWrite
 * @param __u8 reg (Register), __u8 value (1 Byte Value)
 * @return void
 * 
 * Writes Value to I2C Device on Register reg
 * 
 */
void rpiI2cWrite(__u8 reg, __u8 value)
{
	if (i2c_smbus_write_byte_data(fd, reg, value) < 0) {
		close(fd);
		exit(1);
	}
}

/*
 * 
 * name: rpiI2cRead8
 * @param __u8 reg (Register)
 * @return __u8 (1 Byte Data)
 * 
 * Reads 1 Byte Data from I2C Device on Register reg
 * 
 */
__u8 rpiI2cRead8(__u8 reg)
{
	__u8 res = i2c_smbus_read_byte_data(fd, reg);
	
	return res;
}

/*
 * 
 * name: rpiI2cRead16
 * @param __u8 reg (Register)
 * @return __u16 (2 Byte Data)
 * 
 */
__u16 rpiI2cRead16(__u8 reg)
{
	
	__u16 hi = i2c_smbus_read_byte_data(fd, reg);
	__u16 res = (hi << 8) + i2c_smbus_read_byte_data(fd, reg+1);
	
	return res;
}

/*
 * 
 * name: rpiI2cClose
 * @param void
 * @return void
 * 
 */
void rpiI2cClose(void)
{
	close(fd);
}

