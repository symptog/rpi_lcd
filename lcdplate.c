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

int ctr=2;
int backl;
void initMode(void);
void textMode(int);

void toggleBacklight(void)
{
	if(backl==1) {
		lcdBacklight(OFF);
		backl=0;
	}
	else {
		lcdBacklight(ON);
		backl=1;
	}
	usleep(10000);
}

int interrupt4(void)
{
	return lcdButtonPressed(RIGHT) || lcdButtonPressed(LEFT) || lcdButtonPressed(UP) || lcdButtonPressed(DOWN);
}

int interrupt2(void)
{
	return lcdButtonPressed(UP) || lcdButtonPressed(DOWN);
}

void initMode(void)
{
	int i=0;
	while(1) {
		textMode(i);
		if(lcdButtonPressed(RIGHT)) {
			if(i==ctr-1) i=0;
			else i+=1;
		}
		if(lcdButtonPressed(LEFT)){
			if(i==0) i=ctr-1;
			else i-=1;
		}
	}
}

void textMode(int num){
	char szHost[128];
	gethostname(szHost, sizeof(szHost));
	switch(num) {
		case 0:
			lcdClear();
			lcdMessage(szHost);
			lcdMessage("\n~ Date & Time");
			do {
				if(lcdButtonPressed(SELECT)) {
					lcdClear();
					time_t rawtime;
					struct tm * timeinfo;
					time(&rawtime);
					timeinfo=localtime(&rawtime);
					char old='a', new='b';
					int n=32;
					char temp[n];
					while(1) {
						old=new;
						time(&rawtime);
						timeinfo=localtime(&rawtime);
						strftime(temp, n, "%a %b %d %Y\n%H:%M", timeinfo);
						new=temp[20];
						if(old!=new) {
							lcdClear();
							lcdMessage(temp);
						}
						if(lcdButtonPressed(RIGHT)) break;
					}
				}
				if(lcdButtonPressed(RIGHT)) {
					if(num==ctr-1) textMode(0);
					else textMode(num+1);
				}
				if(lcdButtonPressed(LEFT)) {
					if(num==0) textMode(ctr-1);
					else textMode(num-1);
				}
			} while(interrupt2()!=1);
			break;
		case 1:
			lcdClear();
			lcdMessage(szHost);
			lcdMessage("\n~ Mode 1");
			while(interrupt2()!=1) {
				if(lcdButtonPressed(SELECT)) {
					lcdClear();
					lcdMessage("Mode 1");
					//mode1();
				}
				if(lcdButtonPressed(RIGHT)) {
					if(num==ctr-1) textMode(0);
					else textMode(num+1);
				}
				if(lcdButtonPressed(LEFT)) {
					if(num==0) textMode(ctr-1);
					else textMode(num-1);
				}
			}
			break;
	}
}

int main(void)
{ 
	lcdSetup(ADDR, 1);
	/* i2c Address an busnum <- 0 (rev 1) | 1 (rev 2) */
	lcdBacklight(ON);
	lcdClear();
	
	initMode();
	
    return 0;
} 
