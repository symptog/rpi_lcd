/*
 * lcd.h
 * 
 * Created by Tobias Gall <toga@tu-chemnitz.eu>
 * Based on Adafruit's pythen code for CharLCDPlate
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


#ifndef LCD_h
#define LCD_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <linux/types.h>

#include "mcp.c"

#define OUTPUT	0
#define INPUT   1
    
// LED backlight
#define ON   0x07
#define OFF   0x0

// buttons
#define SELECT   0
#define RIGHT   1
#define DOWN   2
#define UP   3
#define LEFT   4

// commands
#define LCD_CLEARDISPLAY   0x01
#define LCD_RETURNHOME   0x02
#define LCD_ENTRYMODESET   0x04
#define LCD_DISPLAYCONTROL   0x08
#define LCD_CURSORSHIFT   0x10
#define LCD_FUNCTIONSET   0x20
#define LCD_SETCGRAMADDR   0x40
#define LCD_SETDDRAMADDR   0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT   0x00
#define LCD_ENTRYLEFT   0x02
#define LCD_ENTRYSHIFTINCREMENT   0x01
#define LCD_ENTRYSHIFTDECREMENT   0x00

// flags for display on/off control
#define LCD_DISPLAYON   0x04
#define LCD_DISPLAYOFF 	0x00
#define LCD_CURSORON   0x02
#define LCD_CURSOROFF   0x00
#define LCD_BLINKON   0x01
#define LCD_BLINKOFF   0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE  0x08
#define LCD_CURSORMOVE  0x00

// flags for display/cursor shift
#define LCD_CURSORMOVE   0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT   0x00

// flags for function set
#define LCD_8BITMODE   0x10
#define LCD_4BITMODE   0x00
#define LCD_2LINE   0x08
#define LCD_1LINE   0x00
#define LCD_5x10DOTS   0x04
#define LCD_5x8DOTS   0x00

#define CHECK_BIT(var,pos) ((var & (1 << pos)) == (1 << pos))

__u8 pin_rs;
__u8 pin_e;
__u8 pin_rw;
__u8 pin_db[4];
__u8 displaycontrol, displayfunction, displaymode, numlines, currline;

void lcdPulseEnable();
void lcdWriteBits(__s8, __u8);
void lcdSetup(__u8, __u8);
void lcdBacklight(__u8);
void lcdClear(void);
void lcdBegin(__u8);
void lcdHome(void);
void lcdSetCurser(__u8, __u8);
void lcdNoDisplay(void);
void lcdDisplay(void);
void lcdNoCursor(void);
void lcdCursor(void);
void lcdNoBlink(void);
void lcdDisplayLeft(void);
void lcdScrollDisplayRight(void);
void lcdLeftToRight(void);
void lcdRightToLeft(void);
void lcdAutoscroll(void);
void lcdNoAutoscroll(void);
__u8 lcdButtonPressed(__u8);
void lcdMessage(char*);
void lcdClose(void);

#endif
