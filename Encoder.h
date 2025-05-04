#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
private:
    volatile int tick = 0;                
    volatile unsigned long timestamp = 0; 
    volatile unsigned long tickInterval = 0; 
    int resolution = 20;

public:
    Encoder();                        
    Encoder(int resolution);          
    void addTick();                  
    int getTicks();                   
    void changeResolution(int newResolution); 
    void setTimestamp(unsigned long time);   
    unsigned long getTimestamp();    
    void setTickInterval(unsigned long time); 
    unsigned long getTickInterval();  
    void reset();
    float getRevolutions(); 
    float getRPM();
};

#endif

