/*
 * lcdplate.c
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


#include <stdio.h>
#include <stdlib.h>

#include "lcd.c"

/* 
 * get i2c address -> 	sudo i2cdetect -y 0 - rpi rev 1
 * 						sudo i2cdetect -y 1 - rpi rev 2
 */

#define ADDR 0x20 // i2c Address

int main(void)
{ 
	lcdSetup(ADDR, 0);
	/* i2c Address an busnum <- 0 (rev 1) | 1 (rev 2) */
	lcdBacklight(ON);
	lcdClear();
	
	
	char* text0 = "Adafruit RGB LCD\nPlate w/Keypad!";
	char* text1 = "Hallo\nWelt";
	//char* text2 = "T e x t 2\nT e x t 2";
	char* text3 = "01234656789!§$%/\n'*+#~-.,<>|";
	char* text4 = "abcdefghijklmn\nopqrstuvwxyz";

	lcdMessage(text0);
	
	while(1) {
		if(lcdButtonPressed(UP)) {
			lcdClear();
			lcdMessage(text1);
		}
		else if(lcdButtonPressed(DOWN)) {
			lcdClose();
		}	
		else if(lcdButtonPressed(RIGHT)) {
			lcdClear();
			lcdMessage(text3);
		}	
		else if(lcdButtonPressed(LEFT)) {
			lcdClear();
			lcdMessage(text4);
		}
		else if(lcdButtonPressed(SELECT)) {
			lcdClear();
			lcdMessage(text0);
		}
	}

    return 0;
} 
