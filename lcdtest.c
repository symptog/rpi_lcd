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
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "lcd.c"

/* 
 * get i2c address -> 	sudo i2cdetect -y 0 - rpi rev 1
 * 						sudo i2cdetect -y 1 - rpi rev 2
 */

#define ADDR 0x20 // i2c Address

int main(void)
{ 
	lcdSetup(ADDR, 1);
	/* i2c Address and busnum <- 0 (rev 1) | 1 (rev 2) */
	lcdBacklight(ON);
	lcdClear();

	lcdMessage("LCD Test Line 1\n");
	lcdMessage("Press any Button!");
	lcdSetCurser(0,1);
	
	while(1) {
		if(lcdButtonPressed(SELECT)) {
			lcdMessage("SELECT          ");
			lcdSetCurser(0,1);
		}
		if(lcdButtonPressed(RIGHT)) {
			lcdMessage("RIGHT           ");
			lcdSetCurser(0,1);
		}
		if(lcdButtonPressed(LEFT)) {
			lcdMessage("LEFT            ");
			lcdSetCurser(0,1);
		}	
		if(lcdButtonPressed(UP)) {
			lcdMessage("UP              ");
			lcdSetCurser(0,1);
		}
		if(lcdButtonPressed(DOWN)) {
			lcdMessage("DOWN            ");
			lcdSetCurser(0,1);
		}
	}
	
    return 0;
} 
