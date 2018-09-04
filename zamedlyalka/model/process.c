#include <stdlib.h>
#include <stdio.h> // printf()

static double wholeTime = 1000;
static double discretFreq = 10;

void
process(size_t *pout_count, double **pout_array, double **pout_timeArray)
{
    *pout_count = 10;
    *pout_timeArray = (double *)malloc(*pout_count * sizeof(double));
    *pout_array = (double *)malloc(*pout_count * sizeof(double));
    for (int i = 0 ; i < *pout_count ; i++)
    {
        (*pout_timeArray)[i] = (double)i;
        (*pout_array)[i] = (double)(i*i);
    }
}
