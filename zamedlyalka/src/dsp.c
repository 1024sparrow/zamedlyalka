#include <stdio.h> // printf()
#include <stdlib.h> // malloc()

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

    int iFreq, iData0;
    double freq, k1, k2, k3, k4, delta;
    for (iFreq = 0 ; iFreq < dsp_data->freqCount ; iFreq++)
    {
        freq = dsp_data->frequences[iFreq];
        for (iData0 = 0 ; iData0 < dsp_data->count ; iData0++)
        {
        }
    }

    return 0;
}
