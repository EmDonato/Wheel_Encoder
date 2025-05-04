#include "Encoder.h"

Encoder::Encoder() {}

Encoder::Encoder(int resolution) {
    this->resolution = resolution;
}

void Encoder::addTick() {
    tick++;
}

int Encoder::getTicks() {
    return tick;
}

void Encoder::changeResolution(int newResolution) {
    resolution = newResolution;
}

void Encoder::setTimestamp(unsigned long time) {
    timestamp = time;
}

unsigned long Encoder::getTimestamp() {
    return timestamp;
}

void Encoder::setTickInterval(unsigned long time) {
    tickInterval = time;
}

unsigned long Encoder::getTickInterval() {
    return tickInterval;
}

void Encoder::reset() {
    tick = 0;
    timestamp = 0;
    tickInterval = 0;
}

float Encoder::getRevolutions() {
    return (float)tick / resolution;
}

float Encoder::getRPM() {
    if (tickInterval == 0) return 0.0;
    return (60.0 * 1e6) / (tickInterval * resolution);  // RPM = (1 min / tempo per giro)
}



