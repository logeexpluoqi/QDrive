/*
 * @Author: luoqi 
 * @Date: 2023-07-02 02:48:08 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-07-02 02:53:41
 */

#ifndef _COMMON_H
#define _COMMON_H

#include <string.h>
#include "bsp/bsp.h"

#define QSH(args)                bsp_printf(args)

#define QSH_INFO_PARAM_ERR      bsp_printf(" #! parameter error !\n"); return 0

#define ISARG(s1, s2)           (strcmp(s1, s2) == 0)

#define QSH_EXPORT(name, callback, desc)    MSH_CMD_EXPORT_ALIAS(callback, name, desc)

#endif
