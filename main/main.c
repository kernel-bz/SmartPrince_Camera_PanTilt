/**
 *	file name:  SmartPrince_PanTilt/main/main.c
 *	author:     Jung,JaeJoon (rgbi3307@nate.com) on the www.kernel.bz
 *	comments:   Camera Pan-Tilt Module for SmartPrince
 *  This is under the GPL License (see <http://www.gnu.org/licenses/>)
 */

#include <stdio.h>
#include <stdlib.h>
#include "wiringPi.h"

#include "devices/serial.h"
#include "devices/i2c.h"
#include "devices/motor.h"


MotorControl_T MotorControl = {
    .Act = MD_STOP,
    .Dir = MD_CENTER,
};

static void _main_dev_init (void)
{
    wiringPiSetup();
}

///
///int motor: dc motor selection(1:Left, 2:Right, 3:Camera Bottom, 4:Camera Top)
///int dir: dc motor direction(0:CCW, 1:CW)
///int speed: dc motor speed(2:20%, 3:30%, 4:40%, 5:50%, 6:60%, 7:70%, 8:80%, 9:90%)
///int duration: dc motor duration(interger 1 to 64)
static void _main_dev_i2c (int motor, int dir, int speed, int duration)
{
    if (motor < MI_CAM_UPPER || motor > MI_CAM_BOTTOM) {
        printf("Motor Index must be 3 or 4\n");
        return;
    }

    if (dir < MD_CCW || dir > MD_CW) {
        printf("Motor Direction must be 0 or 1\n");
        return;
    }

    if (speed < 2) speed = 0;
    if (speed > 7) speed = 7;

    if (duration < 1) duration = 1;
    if (duration > 63) duration = 63;

    dir <<= 5;
    motor -= 1;
    motor <<= 3;

    i2c_init();
    i2c_command(MC_DAT_0 | duration);
    i2c_command(MC_DAT_1 | dir | motor | speed);
    i2c_close();
}

static void _main_dev_serial(int motor, int dir, int speed, int duration)
{
    char cmd[40] = {0,};

     if (motor < MI_CAM_UPPER || motor > MI_CAM_BOTTOM) {
        printf("Motor Index must be 3 or 4\n");
        return;
    }

    if (dir < MD_CCW || dir > MD_CW) {
        printf("Motor Direction must be 0 or 1\n");
        return;
    }

    if (speed < 1) speed = 1;
    if (speed > 9) speed = 9;

    if (duration < 1) duration = 1;
    if (duration > 63) duration = 63;

    serial_open (DEV_SERIAL_NODE, 0);
    sprintf(cmd, "AT+MDTR=%d,%d,%d,%d\r\n",  motor, speed, dir, duration);
    serial_send(cmd);

    serial_close();
}

/**
  cmdline argv:
    1: operation mode (0:I2C, 1:Serial)
    2: dc motor selection
    3: dc motor direction
    4: dc motor speed
    5: dc motor duration
*/
int main(int argc, char **argv)
{
    int mode, motor, dir, speed, duration;

    if (argc > 5) {
        mode = atoi(argv[1]);
        motor = atoi(argv[2]);
        dir = atoi(argv[3]);
        speed = atoi(argv[4]);
        duration = atoi(argv[5]);
    } else if (argc > 3) {
        mode = atoi(argv[1]);
        motor = atoi(argv[2]);
        dir = atoi(argv[3]);
        speed = 5;
        duration = 10;
    } else {
        printf("Usage: ./SmartPrince_PanTilt <mode> <motor> <dir> <speed> <duration>\n");
        return 0;
    }

    _main_dev_init();

    if (mode==1) {
        _main_dev_serial(motor, dir, speed, duration);
    } else {
        _main_dev_i2c(motor, dir, speed, duration);
    }

    return 0;
}
