/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:10
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-03 19:58
 * @ Description:
 */

#include <stdbool.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "init.h"
#include "common.h"
#include "tasks/qblc.h"
#include "bsp/bsp.h"

static void blink(void *args)
{
    static bool state = false;
    while(1){
        state = !state;
        if(state){
            bsp_pin_set(BSP_PIN_BLINK, BSP_PIN_HIGH);
        }else{
            bsp_pin_set(BSP_PIN_BLINK, BSP_PIN_LOW);
        }
        bsp_delay_ms(1000);
    }
}

int init()
{
    if(bsp_init() < 0){
        QSH(" #! bsp init failed\n");
    }
    rt_thread_t tid = rt_thread_create("blink", blink, RT_NULL, 256, 5, 1);
    if(tid != RT_NULL){
        rt_thread_startup(tid);
    }else{
        QSH(" #! blink thread create failed\n");
    }
    if(qblc_init() < 0){
        QSH(" #! qblc init faild\n");
    }
    return 0;
}
