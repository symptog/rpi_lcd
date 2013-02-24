rpi_lcd
=======

raspberry_pi_adafruit_charlcdplate_c


Tested on Rasbian

Testing:

- $ make lcdtest
- $ sudo ./lcdtest

Requirements:
- $ sudo apt-get install i2c-tools libi2c-dev

Usage for 16x2 Adafruit LCD:
- include "lcd.c" from local dir
- call lcdSetup(ADDR, 1); (1st pram: i2c-address, 2nd pram: smbus number)
- use the lcd functions ;)

Usage for controlling the MCP23017:
- include "mcp.c" from local dir
- call mcpSetup(ADDR, 1); (1st pram: i2c-address, 2nd pram: smbus number)
- use the mcp functions (look at mcp.c for details)

Using any other i2c device:
- include "rpii2c.c" from local dir
- call rpiI2cSetup(ADDR, 1); (1st pram: i2c-address, 2nd pram: smbus number)
- use rpiI2cWrite to write to the bus
- use rpiI2cRead8/16 to read from the bus
- or use the i2c_smbus functions directly

Release notes:

+ added pwmdriver.h/.c to support adafruits pwmdriver board (untested)

- removed smbus.* files and includes
+ using smbus from i2c-dev.h
