/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:18
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-02 23:40
 * @ Description:
 */

#include "qblc_dev.h"
#include "bsp.h"
#include "../common.h"

static QblcObj dev;

int qblc_dev_init()
{
    motor_init(&dev.motor_l, 0, 100, 0, 0);
    motor_init(&dev.motor_r, 0, 100, 0, 0);
    motor_enc_init(&dev.motor_l, 0, 1000, 0.09, 5, MOTOR_DIR_CCW);
    motor_enc_init(&dev.motor_r, 0, 1000, 0.09, 5, MOTOR_DIR_CCW);
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
