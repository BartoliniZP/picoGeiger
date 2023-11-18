#ifndef PULSECOUNTER_H
#define PULSECOUNTER_H

#include <deque>
#include <memory>

#include "pico/stdlib.h"
class iPulseCounterView;
class pulseCounter {
   public:
   private:
    unsigned long totalCount;
    unsigned measurementTime;
    unsigned pulsePin;
    bool counting;
    unsigned currentSecondCount;
    irq_handler_t pulseCallback;
    std::deque<unsigned> lastPeriod;
    repeating_timer secondTimer;
    std::weak_ptr<iPulseCounterView> view;

   public:
    pulseCounter(unsigned measurementTimeInSeconds, unsigned pulsePin);
    ~pulseCounter();
    void startCounting();
    void pauseCounting();
    void onPulse();
    void onSecondPassed();
    bool isCounting();
    void setView(const std::shared_ptr<iPulseCounterView>& ref);
    unsigned getCountsInLastPeriod();
    void setMeasurementTime(unsigned newTime);
    unsigned getMeasurementTime();
    unsigned long getTotalCount();
};

#endif