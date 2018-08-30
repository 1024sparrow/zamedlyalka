#include <stdio.h> // printf()
#include <stdlib.h> // malloc()
#include <math.h> // M_PI

#include "dsp.h"

int process_signal(struct DSP_DATA *dsp_data, double p_startFreq, double p_endFreq, double p_freqStepKoeff, double p_q)
{
    {// Составляем набор частот, по которым будет работать
        double i;
        int counter = 0;
        
        //printf("----------------------\n");
        for (i = p_startFreq ; i < p_endFreq ; i+= i*p_freqStepKoeff)
        {
            //printf("freq %i: %f Hz\n", counter, i);
            counter++;
        }
        //printf("======================\n");
        dsp_data->freqCount = counter;
        dsp_data->frequences = malloc(counter * sizeof(double));
        counter = 0;
        for (i = p_startFreq ; i < p_endFreq ; i+= i*p_freqStepKoeff)
        {
            dsp_data->frequences[counter] = i;
            counter++;
        }
    }

    dsp_data->spectrogram = malloc(dsp_data->freqCount * dsp_data->count * dsp_data->processingChannels * sizeof(double));

    int iChannel, iFreq, iData0, l = dsp_data->processingChannels, o;
    double *p = malloc(dsp_data->count * sizeof(double));
    double *q = malloc(dsp_data->count * sizeof(double));
    double k1, k2, k3, k4;
    double h = 2. * M_PI / (double)(dsp_data->dicretFreq);
    double e, w; // ЭДС вынуждения и собств. частота контура соответвенно
    for (o = 0 ; o < dsp_data->processingChannels ; o++)
    {
        for (iFreq = 0 ; iFreq < dsp_data->freqCount ; iFreq++)
        {
            w = dsp_data->frequences[iFreq];
            p[0] = 0;
            q[0] = 1;
            for (iData0 = l + o ; iData0 < dsp_data->count ; iData0 += l)
            {
                e = dsp_data->data_0[iData0 - l + o];
                k1 = h * (e - w * p[iData0 - l + o] / p_q - w * w * q[iData0 - l + o]);
                k2 = h * (e - w * (p[iData0 - l + o] + k1 / 2.) / p_q - w * w * q[iData0 - l + o]);
                k3 = h * (e - w * (p[iData0 - l + o] + k2 / 2.) / p_q - w * w * q[iData0 - l + o]);
                k4 = h * (e - w * (p[iData0 - l + o] + k3) / p_q - w * w * q[iData0 - l + o]);
                p[iData0] = p[iData0 - l + o] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                k1 = h * p[iData0 - l + o];
                k2 = h * (p[iData0 - l + o] + k1/2.);
                k3 = h * (p[iData0 - l + o] + k2/2.);
                k4 = h * (p[iData0 - l + o] + k3);
                q[iData0] = q[iData0 - l + o] + (k1 + 2. * (k2 + k3) + k4) / 6.;
            }
        }
    }

    return 0;
}
