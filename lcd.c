/*
 * lcd.c
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


#include "lcd.h"

__u8 pin_rs = 15;
__u8 pin_e = 13;
__u8 pin_rw = 14;
__u8 pin_db[4] = {12,11,10,9};
__u8 displaycontrol, displayfunction, displaymode, numlines=2, currline;

void lcdPulseEnable()
{
	mcpOutput(pin_e, 1);
	usleep(2000);
	mcpOutput(pin_e, 0);
}

void lcdWriteBits(__s8 bits, __u8 char_mode)
{
	mcpOutput(pin_rs, char_mode);
	bool z;
	int i;
	for(i=7; i>=4; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
			mcpOutput(pin_db[i-4], 1);
		else
			mcpOutput(pin_db[i-4], 0);
	}
	lcdPulseEnable();
	
	for(i=3; i>=0; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
			mcpOutput(pin_db[i], 1);
		else
			mcpOutput(pin_db[i], 0);
	}
	lcdPulseEnable();
}

void lcdSetup(__u8 adr, __u8 busnum) {
	mcpSetup(adr, busnum);
	mcpConfig(pin_e, OUTPUT);
	mcpConfig(pin_rs, OUTPUT);
	mcpConfig(pin_rw, OUTPUT);
	mcpOutput(pin_rw, 0);
	mcpOutput(pin_e, 0);
	
	int i;
	for(i=0; i<4; i++)
		mcpConfig(pin_db[i], OUTPUT);

	lcdWriteBits(0x33,0);
	lcdWriteBits(0x32,0);
	lcdWriteBits(0x28,0);
	lcdWriteBits(0x0C,0);
	lcdWriteBits(0x06,0);
	
	displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	displayfunction |= LCD_2LINE;
	
	displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	lcdWriteBits(LCD_ENTRYMODESET | displaymode,0);
	
	mcpConfig(6, OUTPUT);
	mcpConfig(7, OUTPUT);
	mcpConfig(8, OUTPUT);
	mcpOutput(6, 0);
	mcpOutput(7, 0);
	mcpOutput(8, 0);
	
	mcpPullup(SELECT, 1);
	mcpPullup(LEFT, 1);
	mcpPullup(RIGHT, 1);
	mcpPullup(UP, 1);
	mcpPullup(DOWN, 1);
	mcpConfig(SELECT, INPUT);
	mcpConfig(LEFT, INPUT);
	mcpConfig(RIGHT, INPUT);
	mcpConfig(UP, INPUT);
	mcpConfig(DOWN, INPUT);
	
}

void lcdBacklight(__u8 color)
{
	mcpOutput(6, ~color & 0x01);
	mcpOutput(7, ~color & 0x02);
	mcpOutput(8, ~color & 0x04);
}

void lcdClear(void)
{
	lcdWriteBits(LCD_CLEARDISPLAY,0);
	usleep(2000);
}

void lcdBegin(__u8 lines)
{
	if(lines > 1)
	{
		numlines = lines;
		displayfunction |= LCD_2LINE;
	}
	currline = 0;
	lcdClear();
}

void lcdHome(void)
{
	lcdWriteBits(LCD_RETURNHOME,0);
}

void lcdSetCurser(__u8 col, __u8 row)
{
	__u8 rowoffsets[4] = {0x00, 0x40, 0x14, 0x54};
	if(row > numlines)
		row = numlines - 1;
	lcdWriteBits(LCD_SETDDRAMADDR | (col + rowoffsets[row]),0);
}

void lcdNoDisplay(void)
{
	displaycontrol &= ~LCD_DISPLAYON;
	lcdWriteBits(LCD_DISPLAYCONTROL | displaycontrol,0);
}

void lcdDisplay(void)
{
	displaycontrol |= LCD_DISPLAYON;
	lcdWriteBits(LCD_DISPLAYCONTROL | displaycontrol,0);
}

void lcdNoCursor(void)
{
	displaycontrol &= ~LCD_CURSORON;
	lcdWriteBits(LCD_DISPLAYCONTROL | displaycontrol,0);
}

void lcdCursor(void) {
	displaycontrol |= LCD_CURSORON;
	lcdWriteBits(LCD_DISPLAYCONTROL | displaycontrol,0);
}

void lcdNoBlink(void)
{
	displaycontrol &= ~LCD_BLINKON;
	lcdWriteBits(LCD_DISPLAYCONTROL | displaycontrol,0);
}

void lcdBlink(void)
{
	displaycontrol |= LCD_BLINKON;
	lcdWriteBits(LCD_DISPLAYCONTROL | displaycontrol,0);
}

void lcdScrollDisplayLeft(void)
{
	lcdWriteBits(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT,0);
}

void lcdScrollDisplayRight(void)
{
	lcdWriteBits(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT,0);
}

void lcdLeftToRight(void)
{
	displaymode |= LCD_ENTRYLEFT;
	lcdWriteBits(LCD_ENTRYMODESET | displaymode,0);
}

void lcdRightToLeft(void)
{
	displaymode &= ~LCD_ENTRYLEFT;
	lcdWriteBits(LCD_ENTRYMODESET | displaymode,0);
}

void lcdAutoscroll(void) {
	displaymode |= LCD_ENTRYSHIFTINCREMENT;
	lcdWriteBits(LCD_ENTRYMODESET | displaymode,0);
}

void lcdNoAutoscroll(void)
{
	displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcdWriteBits(LCD_ENTRYMODESET | displaymode,0);
}

__u8 lcdButtonPressed(__u8 button)
{
	if(button > LEFT)
		return 0;
	else
		return !mcpInput(button);
}

void lcdMessage(char* text)
{
	int i=0;
	int len = strlen(text);
	
	while(i<len) {
		if(text[i]=='\n') 
			lcdWriteBits(0xC0,0);
		else
		{
			lcdWriteBits(text[i], 1);
		}
		i++;
	}
}

void lcdClose(void)
{
	lcdClear();
	lcdBacklight(OFF);
	mcpClose();
}
