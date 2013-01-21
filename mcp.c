/*
 * mcp.c
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

/*
 * mcp handles the communication from and to the MCP23017
 * 
 * pins are handled from 0 to 15
 * 
 */


#include "mcp.h"

__u16 direction; // gets direction for GPIOA and GPIOB

/*
 * 
 * name: mcpSetup
 * @param __u8 addr(i2c Device Address), __u8 busnum
 * @return void
 * 
 * init the MCP23017
 * 
 */
void mcpSetup(__u8 addr, __u8 busnum)
{
	 
	rpiI2cSetup(addr, busnum);
	
	rpiI2cWrite(MCP23017_IODIRA, 0xFF); // all A as INPUT
	rpiI2cWrite(MCP23017_IODIRB, 0xFF); // all B as INPUT
	
	direction = rpiI2cRead8(MCP23017_IODIRA);
	direction |= rpiI2cRead8(MCP23017_IODIRB) << 8;
	
	rpiI2cWrite(MCP23017_GPPUA, 0x00); // write A Latch
	rpiI2cWrite(MCP23017_GPPUB, 0x00); // write B Latch
}

/*
 * 
 * name: mcpChangebit
 * @param __u8 bitmap (bitmap to change), __u8 bit (bitposition to change), __u8 value (new value)
 * @return __u8 new bitmap
 * 
 * example: bitmap: 00011100 , bit: 3, value: 0
 * -> new bitmap: 00010100
 * 
 */
__u8 mcpChangebit(__u8 bitmap, __u8 bit, __u8 value)
{
	if(value == 0){
		return bitmap & ~(1 << bit);
	}
	else if(value == 1) {
		return bitmap | (1 << bit);
	}
	else {
		return bitmap;
	}
}

/*
 * 
 * name: mcpReadChangePin
 * @param __u8 port (Register), __u8 pin (Pin), __u8 (Value), __u8 currvalue (Current Value), __u8 set (1 if currvalue via pram)
 * @return void
 * 
 * changes a bit on position pin in currvalue in Register(port)
 * reads currvalue from Register(port) if set==0
 * and writes the new bitmap to the port
 * 
 */
void mcpReadChangePin(__u8 port, __u8 pin, __u8 value, __u8 currvalue, __u8 set)
{
	if(set==0)
		currvalue = rpiI2cRead8(port);
	__u8 newvalue = mcpChangebit(currvalue, pin, value);
	rpiI2cWrite(port, newvalue);
}

/*
 * 
 * name: mcpPullup
 * @param __u8 pin, __u8 value
 * @return void
 * 
 * creats a pullup resister for pin
 * 
 */
void mcpPullup(__u8 pin, __u8 value)
{
	if(pin < 8)
		mcpReadChangePin(MCP23017_GPPUA, pin, value,0,0);
	else
		mcpReadChangePin(MCP23017_GPPUB, pin-8, value,0,0);
}

/*
 * 
 * name: mcpConfig
 * @param __u8 pin, __u8 mode
 * @return void
 * 
 * sets pin as INPUT or OUTPUT
 * 
 */
void mcpConfig(__u8 pin, __u8 mode)
{
	if(pin < 8)
		mcpReadChangePin(MCP23017_IODIRA, pin, mode,0,0);
	else
		mcpReadChangePin(MCP23017_IODIRB, pin-8, mode,0,0);
}

/*
 * 
 * name: mcpOutput
 * @param __u8 pin, __u8 value
 * @return void
 * 
 * sets output pin as on(1)/off(0)
 * 
 */
void mcpOutput(__u8 pin, __u8 value)
{
	if(pin < 8)
		mcpReadChangePin(MCP23017_GPIOA, pin, value, rpiI2cRead8(MCP23017_OLATA), 1);
	else
		mcpReadChangePin(MCP23017_GPIOB, pin-8, value, rpiI2cRead8(MCP23017_OLATB), 1);
}

/*
 * 
 * name: mcpInput
 * @param __u8 pin
 * @return __u8
 * 
 * returns the state of the input
 * 
 */
__u8 mcpInput(__u8 pin)
{
	__u16 value = rpiI2cRead16(MCP23017_GPIOA);
	__u16 temp = value >> 8;
	value <<= 8;
	value |= temp;
	return value & (1 << pin);
}

__u16 mcpRead16()
{
	__u16 lo = rpiI2cRead8(MCP23017_OLATA);
	__u16 hi = rpiI2cRead8(MCP23017_OLATB);
	return((hi << 8) | lo);
}

void mcpWrite16(__u8 value)
{
	rpiI2cWrite(MCP23017_OLATA, value & 0xFF);
	rpiI2cWrite(MCP23017_OLATB, (value >> 8) & 0xFF);
}

void mcpClose(void)
{
	rpiI2cClose();
}
