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

    return 0;
}
