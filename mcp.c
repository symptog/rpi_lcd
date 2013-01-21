/*
 * mcp.c
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


#include "mcp.h"

__u16 direction;

void mcpSetup(__u8 adr, __u8 busnum)
{
	 
	rpiI2cSetup(adr, busnum);
	
	rpiI2cWrite(MCP23017_IODIRA, 0xFF);
	rpiI2cWrite(MCP23017_IODIRB, 0xFF);
	
	direction = rpiI2cRead8(MCP23017_IODIRA);
	direction |= rpiI2cRead8(MCP23017_IODIRB) << 8;
	
	rpiI2cWrite(MCP23017_GPPUA, 0x00);
	rpiI2cWrite(MCP23017_GPPUB, 0x00);
}

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

void mcpReadChangePin(__u8 port, __u8 pin, __u8 value, __u8 currvalue, __u8 set)
{
	if(set==0)
		currvalue = rpiI2cRead8(port);
	__u8 newvalue = mcpChangebit(currvalue, pin, value);
	rpiI2cWrite(port, newvalue);
}

void mcpPullup(__u8 pin, __u8 value)
{
	if(pin < 8)
		mcpReadChangePin(MCP23017_GPPUA, pin, value,0,0);
	else
		mcpReadChangePin(MCP23017_GPPUB, pin-8, value,0,0);
}

void mcpConfig(__u8 pin, __u8 mode)
{
	if(pin < 8)
		mcpReadChangePin(MCP23017_IODIRA, pin, mode,0,0);
	else
		mcpReadChangePin(MCP23017_IODIRB, pin-8, mode,0,0);
}

void mcpOutput(__u8 pin, __u8 value)
{
	if(pin < 8)
		mcpReadChangePin(MCP23017_GPIOA, pin, value, rpiI2cRead8(MCP23017_OLATA), 1);
	else
		mcpReadChangePin(MCP23017_GPIOB, pin-8, value, rpiI2cRead8(MCP23017_OLATB), 1);
}

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
