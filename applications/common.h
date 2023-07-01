/*
 * @Author: luoqi 
 * @Date: 2023-07-02 02:48:08 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-07-02 02:53:41
 */

#ifndef _COMMON_H
#define _COMMON_H

#include <rtthread.h>
#include <string.h>

#define QSH(...)                rt_kprintf(__VA_ARGS__)

#define QSH_INFO_PARAM_ERR      rt_kprintf(" #! parameter error !\n"); return 0

#define ISARG(s1, s2)           (strcmp(s1, s2) == 0)

#endif
