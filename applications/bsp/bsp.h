/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 23:34
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-10 00:08
 * @ Description:
 */

#ifndef _BSP_H
#define _BSP_H

#include <rtthread.h>
#include <stdint.h>

typedef enum {
    BSP_PWM_5,
} BspPwm;
typedef enum {
    BSP_PWM_CH1 = 1,
    BSP_PWM_CH2 = 2,
    BSP_PWM_CH3 = 3,
    BSP_PWM_CH4 = 4,
} BspPwmChannel;

typedef enum{
    BSP_PIN_BLINK,
    BSP_PIN_DIR1,
    BSP_PIN_DIR2,
    BSP_PIN_DIR3,
    BSP_PIN_DIR4,
} BspPin;

typedef enum {
    BSP_PIN_LOW     = 0,
    BSP_PIN_HIGH    = 1
} BspPinStatus;

typedef enum {
    BSP_ENC_CH3,
    BSP_ENC_CH4,
}BspEncChannel;

typedef int (*HwTimerCallback)(void);

#define bsp_printf(...)     rt_kprintf(__VA_ARGS__)

int bsp_init(void);

int bsp_pin_set(BspPin pin, BspPinStatus status);

int bsp_pwm_set(BspPwm pwm, BspPwmChannel ch, float duty);

int bsp_hwtimer_init(uint32_t timeout_us, HwTimerCallback cb);

int bsp_hwtimer_enc_read(BspEncChannel ch, int32_t *enc);

int bsp_delay_ms(uint32_t ms);

#endif
