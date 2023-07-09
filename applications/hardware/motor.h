/*
 * @Author: luoqi 
 * @Date: 2023-04-03 11:03:16 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-04-03 18:26:45
 */

#ifndef _MOTOR
#define _MOTOR

#include <stdint.h>

typedef enum {
    MOTOR_MOD_IDLE,
    MOTOR_MOD_I,
    MOTOR_MOD_V,
    MOTOR_MOD_P,
} MotorMod;

typedef enum {
    MOTOR_DIR_CW,
    MOTOR_DIR_CCW
} MotorDir;

typedef struct motor
{
    uint32_t ppr;   // pulse per pevolution
    int64_t epos;   // encoder position
    int32_t eorg;   // encoder origin position
    MotorDir dir;   // encoder direction
    float unit;     // 1 pulse unit
    float inc;      // encoder position increase;
    float nms;      // encoder data update interval, n * ms
    int32_t epc;    // encoder twice epos error
    uint32_t tcnt;  // interval time counter
    int32_t tmc;    // t measure method counter

    MotorMod mod;
    float i;        // motor current
    float v;        // motor velocity
    float p;        // motor position
    float ilim;     // current limit, cannot less than 0, 0: no limit
    float vlim;     // velocity limit, cannot less than 0, 0: no limit
    float pllim;    // position lower limit, 0: no limit
    float phlim;    // position higher limit, 0: no limit
    float iref;     // current reference
    float vref;     // velocity reference
    float pref;     // position reference
} MotorObj;

int motor_init(MotorObj *motor, float ilim, float vlim, float pllim, float phlim);

int motor_enc_init(MotorObj *motor, int32_t eorg, uint32_t ppr, float unit, float interval_ms, MotorDir dir);

int motor_zero_set(MotorObj *motor);

int motor_enc_calcu(MotorObj *motor, int64_t epos);

int motor_mod_set(MotorObj *motor, MotorMod mod);

int motor_iset(MotorObj *motor, float i);

int motor_vset(MotorObj *motor, float v);

int motor_pset(MotorObj *motor, float p);

#endif