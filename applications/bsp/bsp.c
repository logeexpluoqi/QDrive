/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 23:34
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-10 00:04
 * @ Description:
 */

#include <stdlib.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "bsp.h"
#include "../common.h"

static rt_base_t pin_dir1, pin_dir2, pin_dir3, pin_dir4, pin_blink;
static struct rt_device_pwm *pwm5 = RT_NULL;

#define PWM_PERIOD          50000      // ns
#define PWM_PULSE_BASIC     500

static rt_device_t enc3 = RT_NULL, enc4 = RT_NULL;

static rt_device_t tim11;
static rt_hwtimerval_t timeout_s;

static HwTimerCallback hwtimer_cb = RT_NULL;

static inline rt_err_t tim11_callback(rt_device_t dev, rt_size_t size)
{
    return hwtimer_cb();
}

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
    pwm5 = (struct rt_device_pwm *)rt_device_find("pwm5");
    if(pwm5 == RT_NULL){
        QSH(" #! pwm device find faild\n");
        return -1;
    }
    rt_pwm_set(pwm5, 1, PWM_PERIOD, 0);
    rt_pwm_set(pwm5, 2, PWM_PERIOD, 0);
    rt_pwm_set(pwm5, 3, PWM_PERIOD, 0);
    rt_pwm_set(pwm5, 4, PWM_PERIOD, 0);
    rt_pwm_enable(pwm5, 1);
    rt_pwm_enable(pwm5, 2);
    rt_pwm_enable(pwm5, 3);
    rt_pwm_enable(pwm5, 4);

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

int bsp_pwm_set(BspPwm pwm, BspPwmChannel ch, float duty)
{
    if(duty > 100){
        duty = 100;
    }else if(duty < 0){
        duty = 0;
    }
    switch(pwm){
        case BSP_PWM_5:
            rt_pwm_set(pwm5, ch, PWM_PERIOD, duty * PWM_PULSE_BASIC);
            break;
        default:
            return -1;
    }
    return 0;
}

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

int bsp_hwtimer_enc_read(BspEncChannel ch, int32_t *enc)
{
    int32_t enc_count;
    switch(ch){
        case BSP_ENC_CH3:
            rt_device_read(enc3, 0, &enc_count, sizeof(enc_count));
            rt_device_control(enc3, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
            break;
        case BSP_ENC_CH4:
            rt_device_read(enc4, 0, &enc_count, sizeof(enc_count));
            rt_device_control(enc4, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
            break;
        default:
            return -1;
    }
    *enc = enc_count;
    return 0;
}

int bsp_delay_ms(uint32_t ms)
{
    return rt_thread_mdelay(ms);
}

static int bsp_help()
{
    QSH(" -pin <num> <status>, num[b/1/2/3/4], status[h/l]\n");
    QSH(" -pwm <ch> <duty>, ch[1~4], duty[0.0~00.0]\n");
    return 0;
}

static int cmd_bsp(int argc, char **argv)
{
    if(argc == 1){
        return bsp_help();
    }
    if((argc == 4) && ISARGV(argv[1], "pin")){
        int pin = -1;
        if(ISARGV(argv[2], "b")){
            pin = BSP_PIN_BLINK;
        }else{
            pin = atoi(argv[2]);
        }
        if(ISARGV(argv[3], "l")){
            bsp_pin_set(pin, BSP_PIN_LOW);
        }else if(ISARGV(argv[3], "h")){
            bsp_pin_set(pin, BSP_PIN_HIGH);
        }else {
            QSH_INFO_PARAM_ERR;
        }
    }else if((argc == 4) && ISARGV(argv[1], "pwm")){
        int ch = atoi(argv[2]);
        float duty = atof(argv[3]);
        if((ch >= 1) && (ch <=4)){
            bsp_pwm_set(BSP_PWM_5, ch, duty);
        }else {
            QSH_INFO_PARAM_ERR;
        }
    }else {
        QSH_INFO_PARAM_ERR;
    }
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_bsp, bsp, board surport debug);
