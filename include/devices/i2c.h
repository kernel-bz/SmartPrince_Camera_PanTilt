/*
 *  file name:  i2c.h
 *	comments:   I2C Module for SmartPrince
 *  author:     JungJaeJoon(rgbi3307@nate.com)
 *  Copyright (c) www.kernel.bz
 *  This is under the GPL License (see <http://www.gnu.org/licenses/>)
 */

#ifndef _I2C_H
#define _I2C_H

//I2C Clock: 100KHz
#define I2C_ADDR_SMARTMOTOR     0x15    ///i2cdetect (Master)


void i2c_init (void);
void i2c_close (void);
int i2c_command (int cmd);

#endif
