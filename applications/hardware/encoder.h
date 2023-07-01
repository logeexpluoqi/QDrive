/*
 * @Author: luoqi 
 * @Date: 2023-04-03 11:07:24 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-04-04 17:12:41
 */

#ifndef _ENCODER_H
#define _ENCODER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ENC_DIR_CW,
    ENC_DIR_CCW
} EncoderDir;

typedef struct encoder
{
    uint32_t ppr;   // pulse per pevolution
    int64_t epos;   // encoder position
    int32_t eorg;   // encoder origin position
    EncoderDir dir; // encoder direction
    float unit;     // 1 pulse unit
    float pos;      // encoder position
    float vel;      // encoder mearsure velocity, unit/s
    float inc;      // encoder position increase;
    float interval; // encoder data update interval, n * ms

    int32_t epc;    // encoder twice epos error
    uint32_t tcnt;  // interval time counter
    int32_t tmc;    // t measure method counter

    bool isupdate;
} EncoderObj;

int encoder_init(EncoderObj *enc, int32_t eorg, uint32_t ppr, float unit, float interval, EncoderDir dir);

int encoder_zero_set(EncoderObj *enc);

int encoder_calcu(EncoderObj *enc, int64_t epos);

#endif
