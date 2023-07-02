/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 23:34
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-03 00:39
 * @ Description:
 */

#ifndef _BSP_H
#define _BSP_H

#include <stdint.h>

int bsp_init(void);

typedef int (*HwTimerCallback)(void);
int bsp_hwtimer_init(uint32_t timeout_us, HwTimerCallback cb);

#endif
