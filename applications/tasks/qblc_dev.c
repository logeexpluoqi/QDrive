/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:18
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-02 17:29
 * @ Description:
 */

#include "qblc_dev.h"
#include "../common.h"

static QblcObj dev;

int qblc_dev_init()
{
    motor_init(&dev.motor_l, 0, 100, 0, 0);
    motor_init(&dev.motor_r, 0, 100, 0, 0);
    encoder_init(&dev.enc_l, 0, 1000, 0.09, 5, ENC_DIR_CCW);
    encoder_init(&dev.enc_r, 0, 1000, 0.09, 5, ENC_DIR_CCW);
    return 0;
}

static int cmd_qblc(int argc, char **argv)
{
    return 0;
};
QSH_EXPORT(qblc, cmd_qblc, qblc commands);
