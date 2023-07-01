/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:10
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-02 03:25
 * @ Description:
 */

#include "init.h"
#include "common.h"
#include "tasks/qblc.h"

int init()
{
    if(qblc_init() < 0){
        QSH(" #! qblc init faild\n");
    }
    return 0;
}
