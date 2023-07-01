/*
 * @Author: luoqi 
 * @Date: 2022-03-15 10:01:18 
 * @Last Modified by: luoqi
 * @Last Modified time: 2023-04-03 13:31:17
 */

#include "lpf_sa.h"
#if LPF_SA_USING_LIBC
 #include <stdlib.h>
 #include <string.h>
#endif


void lpf_sa_init(LpfSaObj *filter, int wsize)
{
    #if LPF_SA_USING_LIBC
     filter->cache = (float*)malloc(sizeof(float) * wsize);
     memset(filter->cache, 0, sizeof(float) * wsize);
    #endif

    filter->wsize = wsize;
    filter->sum = 0;
    filter->head = 0;
}

float lpf_sa_calcu(LpfSaObj *filter, float z)
{
    filter->cache[filter->head] = z;
    filter->head = (filter->head + 1) % filter->wsize;
    filter->sum = filter->sum + z - filter->cache[filter->head];

    return (filter->sum / (float)filter->wsize);
}

int lpf_sa_cache_add(LpfSaObj *filter, float *cache, int wsize)
{
    filter->cache = cache;
    filter->wsize = wsize;
    return 0;
}
