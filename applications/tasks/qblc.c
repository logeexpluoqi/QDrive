/**
 * @ Author: luoqi
 * @ Create Time: 2023-07-02 03:23
 * @ Modified by: luoqi
 * @ Modified time: 2023-07-03 01:11
 * @ Description:
 */

#include "qblc.h"
#include "../bsp/bsp.h"
#include "../common.h"

int qblc_init()
{
    if(bsp_init() < 0){
        QSH(" #! qblc drivers init failed\n");
        return -1;
    }
    return 0;
}
