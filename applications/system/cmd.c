/*
 * @Author: luoqi
 * @Date: 2021-04-29 00:29:54
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-07-02 02:46:00
 */

#include <stdlib.h>
#include <string.h>
#include "cmd.h"

#define ASCII_SPACE     0x20
#define ASCII_DOT       0x2c

static LIST_HEAD(cmd_list);
static uint32_t id = 1;

static int qstrcmp(const char* s1, const char* s2);

static CmdErr cmd_exec(char* args)
{
    ListObj* node;
    CmdObj* cmd;
    char* argv[CMD_MAX_NUM + 1] = { 0 };
    int argc = 0;
    int argn = 0;
    int i = 0;

    /* cmd parser */
    do {
        if(i == 0) {
            argv[argn] = &args[i];
        } else if(args[i] == ASCII_SPACE || args[i] == ASCII_DOT) {
            args[i] = 0;
            if(args[i + 1] != ASCII_SPACE && args[i + 1] != ASCII_DOT) {
                argv[++argn] = &args[i + 1];
            }
        }
        i++;
        if(i > CMD_MAX_LEN - 1) {
            return CMD_LEN_OUT;
        }

        if(argn > CMD_MAX_NUM - 1) {
            return CMD_NUM_OUT;
        }

    } while(args[i] != 0);
    /* End of dismantling input command string */
    /* add 1 because there is no space key value front of the first argv */
    argc = argn + 1;
    list_for_each(node, &cmd_list) {
        cmd = list_entry(node, CmdObj, cmd_list);
        if(qstrcmp(cmd->name, argv[0]) == 0) {
            if(cmd->argc != 0xff) {
                if(cmd->argc > argc - 1) {
                    return CMD_PARAM_LESS;
                } else if(cmd->argc < argc - 1) {
                    return CMD_PARAM_EXCEED;
                }
                return cmd->callback(argc, argv);
            } else {
                return cmd->callback(argc, argv);
            }
        }
    }
    return CMD_NO_CMD;
}

int cmd_init(CmdObj* cmd, const char* name, uint8_t argc, CmdCallback callback, const char* usage)
{
    cmd->name = name;
    cmd->argc = argc;
    cmd->id = id;
    cmd->callback = callback;
    cmd->usage = usage;
    id++;
    return 0;
}

int cmd_add(CmdObj* cmd)
{
    if(cmd_isexist(cmd) == 0) {
        list_insert_before(&cmd_list, &cmd->cmd_list);
        return 0;
    } else {
        return -1;
    }
}

int cmd_del(CmdObj* cmd)
{
    if(cmd_isexist(cmd)) {
        list_remove(&cmd->cmd_list);
        return 0;
    } else {
        return -1;
    }
}

int cmd_isexist(CmdObj* cmd)
{
    ListObj* node;
    CmdObj* _cmd;

    list_for_each(node, &cmd_list) {
        _cmd = list_entry(node, CmdObj, cmd_list);
        if(cmd->id == _cmd->id) {
            return 1;
        } else {
            continue;
        }
    }
    return 0;
}

uint32_t cmd_num()
{
    return list_len(&cmd_list);
}

int qstrcmp(const char* s1, const char* s2)
{
    uint32_t i = 0;

    while(s1[i] != 0 || s2[i] != 0) {
        if(s1[i] != s2[i]) {
            return 1;
        } else {
            i++;
        }
    }

    return 0;
}

int cmd_call(const char *args)
{
    char _args[CMD_MAX_LEN + 1] = {0};
    strcpy(_args, args);
    return cmd_exec(_args);
}

int cmd_creat(const char *name, CmdCallback cb)
{
    CmdObj *cmd = (CmdObj *) malloc(sizeof(CmdObj));
    cmd_init(cmd, name, 0xff, cb, NULL);
    cmd_add(cmd);
    return 0;
}
