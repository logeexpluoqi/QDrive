/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:18
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-10 00:15
 * @ Description:
 */

#include <stdint.h>
#include "qblc_dev.h"
#include "bsp/bsp.h"
#include "../common.h"

#define QBLC_ENC_INTERVAL_MS   2

static QblcObj dev;

static int enc_cb()
{
    int32_t enc_l, enc_r;
    bsp_hwtimer_enc_read(BSP_ENC_CH3, &enc_l);
    bsp_hwtimer_enc_read(BSP_ENC_CH4, &enc_r);
    dev.motor_l.epos += enc_l;
    dev.motor_r.epos += enc_r;
    motor_enc_calcu(&dev.motor_l, dev.motor_l.epos);
    motor_enc_calcu(&dev.motor_r, dev.motor_r.epos);
    return 0;
}

int qblc_dev_init()
{
    motor_init(&dev.motor_l, 0, 100, 0, 0);
    motor_init(&dev.motor_r, 0, 100, 0, 0);
    bsp_hwtimer_init(QBLC_ENC_INTERVAL_MS * 1000, enc_cb);
    motor_enc_init(&dev.motor_l, 0, 100, 0.9, QBLC_ENC_INTERVAL_MS, MOTOR_DIR_CCW);
    motor_enc_init(&dev.motor_r, 0, 100, 0.9, QBLC_ENC_INTERVAL_MS, MOTOR_DIR_CCW);
    return 0;
}

QblcObj *qblc_dev()
{
    return &dev;
}

static int cmd_qblc(int argc, char **argv)
{
    return 0;
};
QSH_EXPORT(qblc, cmd_qblc, qblc commands);
