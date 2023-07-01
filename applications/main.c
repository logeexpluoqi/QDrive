/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-02     RT-Thread    first version
 */

#include "init.h"

int main(void)
{
    if(init() < 0){
        return -1;
    }
    return 0;
}
