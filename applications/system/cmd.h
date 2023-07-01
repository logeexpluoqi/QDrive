/*
 * @Author: luoqi
 * @Date: 2021-04-29 00:30:20
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-07-02 02:54:28
 */

#ifndef _CMD_H
#define _CMD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "../dstruct/ilist.h"
#define CMD_MAX_LEN 60
#define CMD_MAX_NUM 10

typedef enum
{
    CMD_PARAM_ERR = -1,
    CMD_NO_ERR = 0,
    CMD_LEN_OUT = 1,
    CMD_NUM_OUT = 2,
    CMD_NO_CMD = 3,
    CMD_PARAM_EXCEED = 4,
    CMD_PARAM_LESS = 5,
    CMD_EXEC_ERR = 6
} CmdErr;

typedef int (*CmdCallback)(int, char **);
typedef struct cmd_object
{
    const char *name;
    uint32_t id;
    uint8_t argc;
    CmdCallback callback;
    const char *usage;
    ListObj cmd_list;
} CmdObj;

int cmd_init(CmdObj *cmd, const char *name, uint8_t argc, CmdCallback callback, const char *usage);

int cmd_add(CmdObj *cmd);

int cmd_del(CmdObj *cmd);

int cmd_isexist(CmdObj *cmd);

int cmd_creat(const char *name, CmdCallback cb);

int cmd_call(const char *args);

#ifdef __cplusplus
}
#endif

#endif
