/**
 *  file name:  i2c.c
 *	  comments:   i2c Module for SmartPrince
 *  author:     JungJaeJoon(rgbi3307@nate.com)
 *  Copyright (c) www.kernel.bz
 *  This is under the GPL License (see <http://www.gnu.org/licenses/>)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "wiringPi.h"
#include "wiringPiI2C.h"

#include "devices/i2c.h"
#include "devices/motor.h"


int I2Cfd;
int I2CSending = 0;

///Interrupt Service Routine for Motor
void i2c_isr(void)
{
    MotorControl.Act = MD_STOP;
    I2CSending = -1;    ///stop
    //printf("IRA7() From Motor\n");
}

void i2c_init (void)
{
	wiringPiISR(MOTOR_IRA7, INT_EDGE_RISING, &i2c_isr);	//P27
    pinMode (MOTOR_IRQ7, OUTPUT);
    digitalWrite (MOTOR_IRQ7, LOW);

    I2Cfd = wiringPiI2CSetup (I2C_ADDR_SMARTMOTOR);
    if (I2Cfd < 0)
        printf("I2C Open Error(%d)\n", I2Cfd);
    else
        printf("I2C Open Succeeded(%d)\n", I2Cfd);
}

void i2c_close (void)
{
    close(I2Cfd);
}

int i2c_command (int cmd)
{
	int ret, cnt=0;

    ///Request IRQ for I2C Sending
    digitalWrite (MOTOR_IRQ7, HIGH);
    I2CSending = 0;
    digitalWrite (MOTOR_IRQ7, LOW);

    while(I2CSending >= 0) {
        ret = wiringPiI2CWrite (I2Cfd, cmd);
        //printf("TX data=%02X\n", cmd);

        I2CSending++;
        do {
            cnt++;
            usleep(20000); ///20ms
        } while(I2CSending > 0 && cnt < 200);

        if (cnt >= 200) return 0;

        ret = wiringPiI2CRead(I2Cfd);  ///read between 30ms and 40ms
        //printf("RX data=%02X\n\n", ret);
    }
    usleep(20000); ///20ms
	return ret;
}
