#ifndef DSP_H
#define DSP_H

struct DSP_RESONATOR_DATA {
    int stub; // stub
};

struct DSP_DATA {
    size_t count;
    int processingChannels;
    double *data_0;
    double power; // мощность считается как сумма квадратов отсчётов. Считается по обоим каналам.
    struct DSP_RESONATOR_DATA *resonators;
};

int process_signal();

#endif // DSP_H
