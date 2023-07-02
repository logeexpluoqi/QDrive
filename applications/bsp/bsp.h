/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 23:34
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-03 00:55
 * @ Description:
 */

#ifndef _BSP_H
#define _BSP_H

#include <stdint.h>

typedef enum {
    BSP_PWM_CH1,
    BSP_PWM_CH2,
    BSP_PWM_CH3,
    BSP_PWM_CH4,
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

int bsp_init(void);

int bsp_pin_set(BspPin pin, BspPinStatus status);

typedef int (*HwTimerCallback)(void);
int bsp_hwtimer_init(uint32_t timeout_us, HwTimerCallback cb);

#endif
