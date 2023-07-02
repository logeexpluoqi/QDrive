/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:10
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-02 18:08
 * @ Description:
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "init.h"
#include "common.h"
#include "tasks/qblc.h"

static void blink(void *args)
{
    static rt_bool_t state = RT_FALSE;
    rt_base_t pin = rt_pin_get("PC.13");
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    while(1){
        state = !state;
        if(state){
            rt_pin_write(pin, PIN_HIGH);
        }else{
            rt_pin_write(pin, PIN_LOW);
        }
        rt_thread_mdelay(1000);
    }
}

int init()
{
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
