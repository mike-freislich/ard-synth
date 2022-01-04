#ifndef SAMPLE_H 
#define SAMPLE_H
#include <Arduino.h>

class Sample {
    private:
    uint8_t *data;
    uint16_t _length;
    
    public:
    Sample() {

    }
    
    ~Sample() {
        if (data != NULL)        
            free(data);
    }

    uint16_t length() {
        if (_length == 0) _length = sizeof(data);
        return _length;
    }

    // sample position at number of ticks
    static uint16_t position(Sample sample, uint16_t ticks) {

    }


};

#endif