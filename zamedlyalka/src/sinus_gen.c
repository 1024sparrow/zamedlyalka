#include <sys/types.h>
#include <stdlib.h> // malloc()
#include <math.h> // M_PI

// p_power - ненормированная (т.е. тупо сумма квадратов отклонений от среднего)
double *sinus_gen(double *p_retval, size_t p_count, double p_w, double p_wDiscr, double p_power)
{
    double *retVal = p_retval ? p_retval : malloc(p_count * sizeof(double));
    size_t i;
    double power = 0;
    for (i = 0 ; i < p_count ; i++)
    {
        double cand = sin(2. * (double)M_PI * (double)i / p_w / p_wDiscr);
        //double cand = sin((double)i / p_w / p_wDiscr);
        retVal[i] = cand;
        power += cand * cand;
    }
    for (i = 0 ; i < p_count ; i++)
    {
        retVal[i] *= p_power / power;
    }
    return retVal;
}
