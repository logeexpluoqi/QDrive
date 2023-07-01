/*
 * @Author: luoqi 
 * @Date: 2023-04-03 11:03:16 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-04-03 18:26:45
 */

#ifndef _MOTOR
#define _MOTOR

typedef enum {
    MOTOR_MOD_IDLE,
    MOTOR_MOD_I,
    MOTOR_MOD_V,
    MOTOR_MOD_P,
} MotorMod;

typedef struct motor
{
    MotorMod mod;
    float i;        // motor current
    float v;        // motor velocity
    float p;        // motor position
    float ilim;     // current limit, cannot less than 0
    float vlim;     // velocity limit, cannot less than 0
    float pllim;    // position lower limit
    float phlim;    // position higher limit
    float iref;     // current reference
    float vref;     // velocity reference
    float pref;     // position reference
} MotorObj;

int motor_init(MotorObj *motor, float ilim, float vlim, float pllim, float phlim);

int motor_mod_set(MotorObj *motor, MotorMod mod);

int motor_iset(MotorObj *motor, float i);

int motor_vset(MotorObj *motor, float v);

int motor_pset(MotorObj *motor, float p);

#endif