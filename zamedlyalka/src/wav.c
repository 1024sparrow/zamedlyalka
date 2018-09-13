#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy, malloc

#include "dsp.h"

#define TRUE 1
#define FALSE 0

// https://audiocoding.ru/article/2008/05/22/wav-file-structure.html
/*struct HEADER
{
    // WAV-формат начинается с RIFF-заголовка:

    // Содержит символы "RIFF" в ASCII кодировке
    // (0x52494646 в big-endian представлении)
    char chunkId[4];

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // Это оставшийся размер цепочки, начиная с этой позиции.
    // Иначе говоря, это размер файла - 8, то есть,
    // исключены поля chunkId и chunkSize.
    unsigned long chunkSize;

    // Содержит символы "WAVE"
    // (0x57415645 в big-endian представлении)
    char format[4];

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:
    
    // Содержит символы "fmt "
    // (0x666d7420 в big-endian представлении)
    char subchunk1Id[4];

    // 16 для формата PCM.
    // Это оставшийся размер подцепочки, начиная с этой позиции.
    unsigned long subchunk1Size;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    unsigned short audioFormat;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    unsigned short numChannels;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    unsigned long sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    unsigned long byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    unsigned short blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    unsigned short bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    char subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    unsigned long subchunk2Size;

    // Далее следуют непосредственно Wav данные.
};*/

// WAVE file header format
struct HEADER {
    unsigned char riff[4];                      // RIFF string
    unsigned int overall_size   ;               // overall size of file in bytes
    unsigned char wave[4];                      // WAVE string
    unsigned char fmt_chunk_marker[4];          // fmt string with trailing null char
    unsigned int length_of_fmt;                 // length of the format data
    unsigned int format_type;                   // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    unsigned int channels;                      // no.of channels
    unsigned int sample_rate;                   // sampling rate (blocks per second)
    unsigned int byterate;                      // SampleRate * NumChannels * BitsPerSample/8
    unsigned int block_align;                   // NumChannels * BitsPerSample/8
    unsigned int bits_per_sample;               // bits per sample, 8- 8bits, 16- 16 bits etc
    unsigned char data_chunk_header [4];        // DATA string or FLLR string
    unsigned int data_size;                     // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};
static struct HEADER header;
//static struct DSP_DATA dsp_data;

int readWav(const char *p_filepath, struct DSP_DATA *dsp_data, int p_useShifting)//, int channelCount *po_channelCount, int sampleCopunt)
{
    printf("reading Wav...\n");
    FILE *file = fopen(p_filepath, "r");
    if (!file)
    {
        fprintf(stderr, "не смог открыть wav-файл\n");
        exit(1);
    }
    int read = 0;
	  
    // http://truelogic.org/wordpress/2015/09/04/parsing-a-wav-file-in-c/
    //struct HEADER header;
    unsigned char buffer4[4];
	unsigned char buffer2[2];
	char* seconds_to_time(float seconds);
    // read header parts
    read = fread(header.riff, sizeof(header.riff), 1, file);
    printf("(1-4): %s \n", header.riff);
    read = fread(buffer4, sizeof(buffer4), 1, file);
    printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    // convert little endian to big endian 4 byte int
    header.overall_size  = buffer4[0] |
        (buffer4[1]<<8) |
        (buffer4[2]<<16) |
        (buffer4[3]<<24);
    printf("(5-8) Overall size: bytes:%u, Kb:%u \n", header.overall_size, header.overall_size/1024);
    read = fread(header.wave, sizeof(header.wave), 1, file);
    printf("(9-12) Wave marker: %s\n", header.wave);
    read = fread(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker), 1, file);
    printf("(13-16) Fmt marker: %s\n", header.fmt_chunk_marker);
    read = fread(buffer4, sizeof(buffer4), 1, file);
    printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    // convert little endian to big endian 4 byte integer
    header.length_of_fmt = buffer4[0] |
        (buffer4[1] << 8) |
        (buffer4[2] << 16) |
        (buffer4[3] << 24);
    printf("(17-20) Length of Fmt header: %u \n", header.length_of_fmt);
    read = fread(buffer2, sizeof(buffer2), 1, file); printf("%u %u \n", buffer2[0], buffer2[1]);
    header.format_type = buffer2[0] | (buffer2[1] << 8);
    char format_name[10] = "";
    if (header.format_type == 1)
        strcpy(format_name,"PCM");
    else if (header.format_type == 6)
        strcpy(format_name, "A-law");
    else if (header.format_type == 7)
        strcpy(format_name, "Mu-law");
    printf("(21-22) Format type: %u %s \n", header.format_type, format_name);
    read = fread(buffer2, sizeof(buffer2), 1, file);
    printf("%u %u \n", buffer2[0], buffer2[1]);
    header.channels = buffer2[0] | (buffer2[1] << 8);
    printf("(23-24) Channels: %u \n", header.channels);
    read = fread(buffer4, sizeof(buffer4), 1, file);
    printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    header.sample_rate = buffer4[0] |
        (buffer4[1] << 8) |
        (buffer4[2] << 16) |
        (buffer4[3] << 24);
    printf("(25-28) Sample rate: %u\n", header.sample_rate);
    read = fread(buffer4, sizeof(buffer4), 1, file);
    printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    header.byterate  = buffer4[0] |
        (buffer4[1] << 8) |
        (buffer4[2] << 16) |
        (buffer4[3] << 24);
    printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", header.byterate, header.byterate*8);
    read = fread(buffer2, sizeof(buffer2), 1, file);
    printf("%u %u \n", buffer2[0], buffer2[1]);
    header.block_align = buffer2[0] |
        (buffer2[1] << 8);
    printf("(33-34) Block Alignment: %u \n", header.block_align);
    read = fread(buffer2, sizeof(buffer2), 1, file);
    printf("%u %u \n", buffer2[0], buffer2[1]);
    header.bits_per_sample = buffer2[0] |
        (buffer2[1] << 8);
    printf("(35-36) Bits per sample: %u \n", header.bits_per_sample);
    read = fread(header.data_chunk_header, sizeof(header.data_chunk_header), 1, file);
    printf("(37-40) Data Marker: %s \n", header.data_chunk_header);
    read = fread(buffer4, sizeof(buffer4), 1, file);
    printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    header.data_size = buffer4[0] |
        (buffer4[1] << 8) |
        (buffer4[2] << 16) |
        (buffer4[3] << 24 );
    printf("(41-44) Size of data chunk: %u \n", header.data_size);
    // calculate no.of samples
    long num_samples = (8 * header.data_size) / (header.channels * header.bits_per_sample);
    printf("Number of samples:%lu \n", num_samples);
    long size_of_each_sample = (header.channels * header.bits_per_sample) / 8;
    printf("Size of each sample:%ld bytes\n", size_of_each_sample);
    // calculate duration of file
    float duration_in_seconds = (float) header.overall_size / header.byterate;
    printf("Approx.Duration in seconds=%f\n", duration_in_seconds);
    printf("Approx.Duration in h:m:s=%s\n", seconds_to_time(duration_in_seconds));
    // read each sample from data chunk if PCM
    long i =0;
    if (header.format_type == 1) { // PCM
        dsp_data->processingChannels = 1;
        dsp_data->count = num_samples;
        dsp_data->data_0 = malloc(num_samples * header.channels * sizeof(double));
        dsp_data->discretFreq = header.sample_rate;


        //printf("Dump sample data? Y/N?");
        //char c = 'n';
        //scanf("%c", &c);
        //if (c == 'Y' || c == 'y') {
        if (1) {
            //printf("size of each sample: %lx\n", size_of_each_sample);// output: 4
            unsigned char data_buffer[size_of_each_sample];
            int  size_is_correct = TRUE;
            // make sure that the bytes-per-sample is completely divisible by num.of channels
            int bytes_in_each_channel = (size_of_each_sample / header.channels);
            if ((bytes_in_each_channel  * header.channels) != size_of_each_sample) {
                printf("Error: %ld x %ud <> %ld\n", bytes_in_each_channel, header.channels, size_of_each_sample);
                size_is_correct = FALSE;
            }
            if (size_is_correct) {
                if (header.channels != 1 && header.channels != 2)
                {
                    printf("wav-файлы с количеством каналов %i не поддерживается", header.channels);
                    return 1;
                }
                for (i =1; i <= num_samples; i++) {
                    read = fread(data_buffer, sizeof(data_buffer), 1, file);
                    if (read == 1) {
                        for (int iChannel = 0 ; iChannel < header.channels ; iChannel++)
                        {
                            double cand = 0;
                            if (data_buffer[bytes_in_each_channel - 1] < 128)
                            {
                                for (int iByte = bytes_in_each_channel - 1 ; iByte >= 0 ; iByte--)
                                {
                                    cand *= 256;
                                    cand += data_buffer[iByte];
                                }
                            }
                            else
                            {
                                for (int iByte = bytes_in_each_channel - 1 ; iByte >= 0 ; iByte--)
                                {
                                    cand *= 256;
                                    cand += (255 - data_buffer[iByte]);
                                }
                                cand = -cand;
                            }
                            printf("cand: %f -- %u %u %u %u\n", cand, data_buffer[0], data_buffer[1], data_buffer[2], data_buffer[3]);
                            dsp_data->data_0[iChannel * num_samples + i] - cand;
                        }
                    }
                    else {
                        printf("Error reading file. %d bytes\n", read);
                        return 1;
                    }
                } //    for (i =1; i <= num_samples; i++) {
            } //    if (size_is_correct) {
        } // if (c == 'Y' || c == 'y') {
    } //  if (header.format_type == 1) {
    printf("Closing file..\n");
    fclose(file);

    if (p_useShifting)
    {
        if (header.channels == 2)
        {
            for (i = 0 ; i < dsp_data->count ; i++)
            {
                dsp_data->data_0[i] = (dsp_data->data_0[dsp_data->count + i] + dsp_data->data_0[i]) / 2.;
            }
        }
    }
    else
    {
        if (header.channels == 2)
            dsp_data->processingChannels = 2;
    }
    //printf("Total power: %g\n", dsp_data->power); <-- здесь общая мощность исходного сигнала не вычисляется (и значение переменной неопределённое)

    return 0;
}

/**
 * Convert seconds into hh:mm:ss format
 * Params:
 *  seconds - seconds value
 * Returns: hms - formatted string
 **/
char* seconds_to_time(float raw_seconds) {
    char *hms;
    int hours, hours_residue, minutes, seconds, milliseconds;
    hms = (char*) malloc(100);
    sprintf(hms, "%f", raw_seconds);

    hours = (int) raw_seconds/3600;
    hours_residue = (int) raw_seconds % 3600;
    minutes = hours_residue/60;
    seconds = hours_residue % 60;
    milliseconds = 0;
    // get the decimal part of raw_seconds to get milliseconds
    char *pos;
    pos = strchr(hms, '.');
    int ipos = (int) (pos - hms);
    char decimalpart[15];
    memset(decimalpart, ' ', sizeof(decimalpart));
    strncpy(decimalpart, &hms[ipos+1], 3);
    milliseconds = atoi(decimalpart);
    sprintf(hms, "%d:%d:%d.%d", hours, minutes, seconds, milliseconds);
    return hms;
}

void __(size_t from, char *to, short bytes)
{
    if (bytes == 4)
    {
        to[3] = from & 0xff000000;
        to[2] = from & 0xff0000;
    }
    to[1] = from & 0xff00;
    to[0] = from & 0xff;
}
int writeWav(const char *filepath, const struct DSP_DATA *dsp_data)
{
    FILE *file = fopen(filepath, "w");
    if (!file)
    {
        fprintf(stderr, "Не смог открыть выходной файл для записи.\n");
        exit(1);
    }
    unsigned char buffer4[4];
	unsigned char buffer2[2];
    fwrite(header.riff, sizeof(header.riff), 1, file);
    __(header.overall_size, buffer4, 4); fwrite(buffer4, sizeof(buffer4), 1, file);// не совпадает
    fwrite(header.wave, sizeof(header.wave), 1, file);
    fwrite(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker), 1, file);
    __(header.length_of_fmt, buffer4, 4); fwrite(buffer4, sizeof(buffer4), 1, file);
    __(header.format_type, buffer2, 2); fwrite(buffer2, sizeof(buffer2), 1, file);
    __(2, buffer2, 2);/*два канала*/ fwrite(buffer2, sizeof(buffer2), 1, file);
    __(header.sample_rate, buffer4, 4); fwrite(buffer4, sizeof(buffer4), 1, file);// не совпадает


    __(header.byterate, buffer4, 4); fwrite(buffer4, sizeof(buffer4), 1, file);
    __(header.block_align, buffer2, 2); fwrite(buffer2, sizeof(buffer2), 1, file);
    __(header.bits_per_sample, buffer2, 2); fwrite(buffer2, sizeof(buffer2), 1, file);
    fwrite(header.data_chunk_header, sizeof(header.data_chunk_header), 1, file);
    __(header.data_size, buffer4, 4); fwrite(buffer4, sizeof(buffer4), 1, file);

    long low_limit = 0l;
    long high_limit = 0l;
    switch (header.bits_per_sample) {
        case 8:
            low_limit = -128;
            high_limit = 127;
            break;
        case 16:
            low_limit = -32768;
            high_limit = 32767;
            break;
        case 32:
            low_limit = -2147483648;
            high_limit = 2147483647;
            break;
    }
    //printf("\n\n.Valid range for data values : %ld to %ld \n", low_limit, high_limit);
    int sizeOfEachSample = (2 * header.bits_per_sample) / 8; // два канала
    char dataBuffer[sizeOfEachSample];

    size_t i;
    for (i = 0 ; i < dsp_data->count ; i++)
    {
        //fwrite();
        double real = dsp_data->data_1[i];
        if (real > high_limit)
            real = high_limit;
        if (real < low_limit)
            real = low_limit;
        //unsigned long realLong = real;
        int32_t realLong = real;//(real < 0) ? real + high_limit : real;
        realLong = (real < 0) ? (u_int32_t)(real + 2 * ((unsigned long)high_limit + 1)) : real;
        printf(" %u - %f: %u %u %u %u", realLong, real, (unsigned char)(realLong & 0xff), (unsigned char)(realLong & 0xff00), (unsigned char)(realLong & 0xff0000), (unsigned char)(realLong & 0xff000000));
        //printf(" \t\t\t%u - %f: %ul %u %u %u\n", realLong, real, realLong & 0xff, realLong & 0xff00, realLong & 0xff0000, realLong & 0x8f000000);
        printf("\n");
        /*for (int ii = 0, cc = header.bits_per_sample / 8 ; ii < cc ; ii++)
        {
            char cand = realLong 
        }*/
    }

    fclose(file);
}
