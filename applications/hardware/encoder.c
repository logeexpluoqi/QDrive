/*
 * @Author: luoqi 
 * @Date: 2023-04-03 11:08:06 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-04-04 17:44:42
 */

#include <string.h>
#include "encoder.h"

int encoder_init(EncoderObj *enc, int32_t eorg, uint32_t ppr, float unit, float interval, EncoderDir dir)
{
    memset(enc, 0, sizeof(EncoderObj));
    enc->ppr = ppr;
    enc->eorg = eorg;
    enc->unit = unit;
    enc->interval = interval;
    enc->dir = dir;
    enc->isupdate = false;
    return 0;
}

int encoder_zero_set(EncoderObj *enc)
{
    enc->epos = 0;
    enc->pos = 0;
    enc->vel = 0;
    return 0;
}

int encoder_calcu(EncoderObj *enc, int64_t epos)
{
    if(enc->dir == ENC_DIR_CCW){
        epos = -epos;
    }
    enc->epc = epos - enc->epos;
    enc->inc = enc->epc * enc->unit;
    enc->epos = epos;
    enc->pos = (float)(epos - enc->eorg) * enc->unit;
    if(enc->epc < (0.001f * enc->interval * enc->ppr)){
        enc->tcnt ++;
        enc->tmc += enc->epc;
        if(enc->tcnt > 10){
            enc->tcnt = 0;
            enc->vel = 100 * ((float)enc->tmc * enc->unit) / enc->interval;
            enc->tmc = 0;
        }
    }else{
        enc->vel = 1000 * ((float)enc->epc * enc->unit) / enc->interval;
        enc->tcnt = 0;
        enc->tmc = 0;
    }
    enc->isupdate = true;
    return 0;
}

