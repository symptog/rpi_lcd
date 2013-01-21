/*
 * mcp.h
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


#ifndef	MCP_H
#define MCP_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>

#include "rpii2c.c"

#define MCP23017_IODIRA  0x00
#define MCP23017_IODIRB  0x01
#define MCP23017_GPIOA  0x12
#define MCP23017_GPIOB  0x13
#define MCP23017_GPPUA  0x0C
#define MCP23017_GPPUB  0x0D
#define MCP23017_OLATA  0x14
#define MCP23017_OLATB  0x15

extern __u16 direction;

void mcpSetup(__u8, __u8);
__u8 mcpChangebit(__u8, __u8, __u8);
void mcpReadChangePin(__u8, __u8, __u8, __u8, __u8);
void mcpPullup(__u8, __u8);
void mcpConfig(__u8, __u8);
void mcpOutput(__u8, __u8);
__u8 mcpInput(__u8);
__u16 mcpRead16(void);
void mcpWrite16(__u8);
void mcpClose(void);

#endif
