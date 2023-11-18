#ifndef STOPWATCHMODEL_H
#define STOPWATCHMODEL_H
#include "pico/stdlib.h"
#include "utils/time.h"

class stopwatchModel {
    uint64_t startPoint;
    uint64_t pausePoint : 63;
    bool isGoing : 1;

   public:
    stopwatchModel() = default;
    void start();
    void pause();
    void reset();
    time getCurrentMeasure();
    static time convertUStoTime(uint64_t us);
    bool isRunning();
};

#endif