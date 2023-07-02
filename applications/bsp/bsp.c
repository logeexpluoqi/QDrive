/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 23:34
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-03 01:14
 * @ Description:
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "bsp.h"
#include "../common.h"

static rt_base_t pin_dir1, pin_dir2, pin_dir3, pin_dir4, pin_blink;
static struct rt_device_pwm *pwm = RT_NULL;

#define PWM_PERIOD          100000      // ns
#define PWM_PULSE_BASIC     10

static rt_device_t enc3 = RT_NULL, enc4 = RT_NULL;

static rt_device_t tim11;
static rt_hwtimerval_t timeout_s;
static inline rt_err_t tim11_callback(rt_device_t dev, rt_size_t size);

int bsp_init()
{
    /* pin init */
    pin_dir1 = rt_pin_get("PB.0");
    pin_dir2 = rt_pin_get("PB.1");
    pin_dir3 = rt_pin_get("PB.2");
    pin_dir4 = rt_pin_get("PB.10");
    pin_blink = rt_pin_get("PC.13");

    rt_pin_mode(pin_dir1, PIN_MODE_OUTPUT);
    rt_pin_mode(pin_dir2, PIN_MODE_OUTPUT);
    rt_pin_mode(pin_dir3, PIN_MODE_OUTPUT);
    rt_pin_mode(pin_dir4, PIN_MODE_OUTPUT);
    rt_pin_mode(pin_blink, PIN_MODE_OUTPUT);

    /* pwm init */
    pwm = (struct rt_device_pwm *)rt_device_find("pwm5");
    if(pwm == RT_NULL){
        QSH(" #! pwm device find faild\n");
        return -1;
    }
    rt_pwm_set(pwm, 1, PWM_PERIOD, 0);
    rt_pwm_set(pwm, 2, PWM_PERIOD, 0);
    rt_pwm_set(pwm, 3, PWM_PERIOD, 0);
    rt_pwm_set(pwm, 4, PWM_PERIOD, 0);
    rt_pwm_enable(pwm, 1);
    rt_pwm_enable(pwm, 2);
    rt_pwm_enable(pwm, 3);
    rt_pwm_enable(pwm, 4);

    /* encoder init */
    enc3 = rt_device_find("pulse3");
    if(enc3 == RT_NULL){
        QSH(" #! enc3 find faild\n");
        return -1;
    }
    enc4 = rt_device_find("pulse4");
    if(enc4 == RT_NULL){
        QSH(" #! enc4 find faild\n");
        return -1;
    }

    tim11 = rt_device_find("timer11");
    if(tim11 == RT_NULL){
        QSH(" #! timer11 find faild\n");
        return -1;
    }
    if(rt_device_open(tim11, RT_DEVICE_OFLAG_RDWR) != RT_EOK){
        QSH(" #! timer11 open failed\n");
        return -1;
    }

    return 0;
}

int bsp_pin_set(BspPin pin, BspPinStatus status)
{
    switch(pin){
        case BSP_PIN_BLINK:
            rt_pin_write(pin_blink, status);
            break;
        case BSP_PIN_DIR1:
            rt_pin_write(pin_dir1, status);
            break;
        case BSP_PIN_DIR2:
            rt_pin_write(pin_dir2, status);
            break;
        case BSP_PIN_DIR3:
            rt_pin_write(pin_dir3, status);
            break;
        case BSP_PIN_DIR4:
            rt_pin_write(pin_dir4, status);
            break;
        default:
            return -1;
    }
    return 0;
}

int bsp_pwm_set()
{
    
    return 0;
}

static HwTimerCallback hwtimer_cb = RT_NULL;

int bsp_hwtimer_init(uint32_t timeout_us, HwTimerCallback cb)
{
    uint32_t freq_ns = 1000;
    hwtimer_cb = cb;
    rt_device_set_rx_indicate(tim11, tim11_callback);
    rt_device_control(tim11, HWTIMER_CTRL_FREQ_SET, &freq_ns);
    rt_hwtimer_mode_t mode = HWTIMER_MODE_PERIOD;
    rt_device_control(tim11, HWTIMER_CTRL_MODE_SET, &mode);
    timeout_s.sec = 0;
    timeout_s.usec = timeout_us;
    if(rt_device_write(tim11, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s)){
        QSH(" #! timer11 timeout set failed\n");
        return -1;
    }
    return 0;
}

rt_err_t tim11_callback(rt_device_t dev, rt_size_t size)
{
    return hwtimer_cb();
}
