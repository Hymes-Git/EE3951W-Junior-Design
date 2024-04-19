#include "xc.h"

#define BUFSIZE 128
#define SampleSize 16

static int adc_buffer[BUFSIZE];
static int buffer_index = 0;

// takes a value and adds it into the next slot of the buffer
void putVal(int newValue)
{
    adc_buffer[buffer_index] = newValue;
    buffer_index++;
    if (buffer_index == BUFSIZE)
        buffer_index = 0;
}

// returns the average value of all sample size last values stored in the buffer
int getAvg()
{
    long int sum = 0;
    int returnval;
    int i;
    int numtoadd = 0;
    int temp_index = buffer_index - 1;

    for (i = 0; i < SampleSize; i++)
    {
        // code goes backwards so if the current index is 0 it is set to the max index
        if (temp_index == 0)
            temp_index = BUFSIZE - 1;

        // adds the current index and then decrements it
        numtoadd = adc_buffer[temp_index];
        temp_index--;

        sum += numtoadd;
    }

    returnval = sum >> 4; // divide by 16

    return returnval;
}

// fills the buffer with 0s
void initBuffer()
{
    int i;
    for (i = 0; i < BUFSIZE; i++)
        adc_buffer[i] = 0;
}
