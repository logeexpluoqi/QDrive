/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:18
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-02 03:23
 * @ Description:
 */

#ifndef _QBLC_DEV_H
#define _QBLC_DEV_H

#include "../hardware/motor.h"
#include "../hardware/encoder.h"

typedef struct qblc_dev{
    MotorObj motor_l;
    MotorObj motor_r;
    EncoderObj enc_l;
    EncoderObj enc_r;

} QblcObj; // Q balance car

int qblc_dev_init(void);

#endif
