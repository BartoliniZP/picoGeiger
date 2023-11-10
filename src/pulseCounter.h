#ifndef PULSECOUNTER_H
#define PULSECOUNTER_H
#include <deque>
#include <memory>

#include "pico/stdlib.h"
class pulseCounter {
   public:
    struct iPulseCounterView {
        virtual void updateMeasurement() = 0;  // this function is called on timer callback, it should be lightweight e.g. only annotating that measurement should be changed, real actions about measurement changes should happen in main loop
        virtual ~iPulseCounterView() noexcept = default;
    };

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