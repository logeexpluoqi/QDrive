/*
 * @Author: luoqi 
 * @Date: 2023-04-03 11:06:30 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-04-04 17:28:08
 */

#include <string.h>
#include "motor.h"

int motor_init(MotorObj *motor, float ilim, float vlim, float pllim, float phlim)
{
    memset(motor, 0, sizeof(MotorObj));
    motor->mod = MOTOR_MOD_IDLE;
    motor->ilim = ilim;
    motor->vlim = vlim;
    motor->pllim = pllim;
    motor->phlim = phlim;
    return 0;
}

int motor_enc_init(MotorObj *motor, int32_t eorg, uint32_t ppr, float unit, float interval_ms, MotorDir dir)
{
    motor->ppr = ppr;
    motor->eorg = eorg;
    motor->unit = unit;
    motor->nms = interval_ms;
    motor->dir = dir;
    return 0;
}

int motor_zero_set(MotorObj *motor)
{
    motor->epos = 0;
    motor->p = 0;
    motor->v = 0;
    return 0;
}

int motor_enc_calcu(MotorObj *motor, int64_t epos)
{
    if(motor->dir == MOTOR_DIR_CCW){
        epos = -epos;
    }
    motor->epc = epos - motor->epos;
    motor->inc = motor->epc * motor->unit;
    motor->epos = epos;
    motor->p = (float)(epos - motor->eorg) * motor->unit;
    if(motor->epc < (0.001f * motor->nms * motor->ppr)){
        motor->tcnt ++;
        motor->tmc += motor->epc;
        if(motor->tcnt > 10){
            motor->tcnt = 0;
            motor->v = 100 * ((float)motor->tmc * motor->unit) / motor->nms;
            motor->tmc = 0;
        }
    }else{
        motor->v = 1000 * ((float)motor->epc * motor->unit) / motor->nms;
        motor->tcnt = 0;
        motor->tmc = 0;
    }
    return 0;
}

int motor_mod_set(MotorObj *motor, MotorMod mod)
{
    motor->mod = mod;
    return 0;
}

int motor_iset(MotorObj *motor, float i)
{
    if(motor->ilim == 0.0f){
        motor->iref = i;
    }else{
        motor->iref = (i > motor->ilim) ? motor->ilim : ((i < -motor->ilim) ? -motor->ilim : i);
    }
    return 0;
}

int motor_vset(MotorObj *motor, float v)
{
    if(motor->vlim == 0.0f){
        motor->vref = v;
    }else{
        motor->vref = (v > motor->vlim) ? motor->vlim : ((v < -motor->vlim) ? -motor->vlim : v);
    }
    return 0;
}

int motor_pset(MotorObj *motor, float p)
{
    if((motor->phlim == 0.0f) && (motor->pllim == 0.0f)){
        motor->pref = p;
    }else{
        motor->pref = (p > motor->phlim) ? motor->phlim : ((p < motor->pllim) ? motor->pllim : p);
    }
    return 0;
}
