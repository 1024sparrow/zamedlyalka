#include <stdlib.h>
#include <stdio.h> // printf()
#include <math.h>

double *sinus_gen(double *p_retval, size_t p_count, double p_w, double p_wDiscr, double p_power); // implemented in sinus_gen.c

static double wholeTime = 1;
static double discretFreq = 10000;
static double p_q = 20;

void
process(size_t *pout_count, double **pout_array, double **pout_timeArray)
{
    printf("process");
    *pout_count = wholeTime * discretFreq;
    *pout_timeArray = (double *)malloc(*pout_count * sizeof(double));
    *pout_array = (double *)malloc(*pout_count * sizeof(double));
    double *p = malloc(*pout_count * sizeof(double)); // сила тока от времени
    double *q = malloc(*pout_count * sizeof(double)); // заряд от времени
    double k1, k2, k3, k4;
    double h = 1./(double)(discretFreq);
    //double h = 1. / (double)(dsp_data->discretFreq);
    //double h = 1;
    double e, w; // ЭДС вынуждения и собств. частота контура соответвенно
    w = 50;
    double *sinus = sinus_gen(0, *pout_count, 60, discretFreq, 100);
    p[0] = 0;
    q[0] = 0;
    //w = w /2./(double)M_PI;
    for (size_t iData0 = 1; iData0 < *pout_count ; iData0++)
    {
        //e = dsp_data->data_0[iData0 - 1];
        //e = (dsp_data->data_0[(iData0 - 1) * l + o] + dsp_data->data_0[(iData0) * l + o])/2.;// / 1e16;
        e = sinus[iData0];// + sinus[iData0 - 1]) / 2.;

        (*pout_timeArray)[iData0] = (double)iData0 * h;
        (*pout_array)[iData0] = e;//(double)(iData0*iData0);

        //printf(" %g", e);
        k1 = 2.*(double)M_PI * h * (e - w * p[iData0 - 1] / p_q - w * w * q[iData0]);
        k2 = 2.*(double)M_PI * h * (e - w * (p[iData0 - 1] + k1 / 2.) / p_q - w * w * q[iData0 - 1]);
        k3 = 2.*(double)M_PI * h * (e - w * (p[iData0 - 1] + k2 / 2.) / p_q - w * w * q[iData0 - 1]);
        k4 = 2.*(double)M_PI * h * (e - w * (p[iData0 - 1] + k3) / p_q - w * w * q[iData0 - 1]);
        p[iData0] = p[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
        //mean += p[iData0];
        k1 = 2.*(double)M_PI * h * p[iData0 - 1];
        k2 = 2.*(double)M_PI * h * (p[iData0 - 1] + k1/2.);
        k3 = 2.*(double)M_PI * h * (p[iData0 - 1] + k2/2.);
        k4 = 2.*(double)M_PI * h * (p[iData0 - 1] + k3);
        q[iData0] = q[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;

        (*pout_array)[iData0] = p[iData0];
    }


    /*for (int i = 0 ; i < *pout_count ; i++)
    {
        (*pout_timeArray)[i] = (double)i;
        (*pout_array)[i] = (double)(i*i);
    }*/
}
