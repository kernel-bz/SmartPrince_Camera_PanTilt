//
//	file name: motor.h
//	comments: Motor Control Module
//	author: Jung,JaeJoon(rgbi3307@nate.com) at the www.kernel.bz
//

#ifndef _MOTOR_H
#define _MOTOR_H

#define	MOTOR_IRQ7      10  ///P24
#define	MOTOR_IRA7      27  ///P36

///Motor Select Index
#define MI_NONE         0
#define MI_LEFT         1
#define MI_RIGHT        2
#define MI_CAM_UPPER    3   ///Camera Upper for Tilt Control
#define MI_CAM_BOTTOM   4   ///Camera Bottom for Pan Control
#define MI_ALL          5

///Motor Direction
#define MD_STOP         0
#define MD_CENTER       0
#define MD_UP           1
#define MD_DOWN         2
#define MD_LEFT         4
#define MD_RIGHT        8

#define MD_CCW          0   ///Right, Backward(Up)
#define MD_CW           1   ///Left, Forward(Down)

#define MC_DAT_0        0 << 7
#define MC_DAT_1        1 << 7
#define MC_DAT_2        2 << 7
#define MC_DAT_3        3 << 7
#define MC_DIR_CCW      MD_CCW << 5
#define MC_DIR_CW       MD_CW << 5
#define MC_IDX_1        0 << 3
#define MC_IDX_2        1 << 3
#define MC_IDX_3        2 << 3
#define MC_IDX_4        3 << 3


typedef struct  {
    int Act;
    int Dir;
} MotorControl_T;

///define in main.c
extern MotorControl_T MotorControl;


#endif

