#include "pulseCounter.h"
#define irqEgdeLowEventMask 0b100

#include <numeric>

#include "../utils/callableWrapper.hpp"
#include "iPulseCounterView.h"
pulseCounter::pulseCounter(unsigned measurementTimeInSeconds, unsigned pulsePin) : totalCount(0), measurementTime(measurementTimeInSeconds), pulsePin(pulsePin), counting(false), currentSecondCount(0), pulseCallback(wrapper([this, pulsePin]() { 
            if(gpio_get_irq_event_mask(pulsePin)&irqEgdeLowEventMask) {
            gpio_acknowledge_irq(pulsePin, irqEgdeLowEventMask);
            this->onPulse();
            } })), lastPeriod(measurementTime, 0) {
    gpio_init(pulsePin);
    gpio_set_dir(pulsePin, GPIO_IN);
    gpio_pull_down(pulsePin);
}

pulseCounter::~pulseCounter() {
    pauseCounting();
    gpio_disable_pulls(pulsePin);
    gpio_deinit(pulsePin);
}

void pulseCounter::startCounting() {
    if (!counting) {
        lastPeriod = std::deque<unsigned>(measurementTime, 0);
        gpio_set_irq_enabled(pulsePin, irqEgdeLowEventMask, true);
        gpio_add_raw_irq_handler(pulsePin, pulseCallback);
        add_repeating_timer_ms(
            1000,
            [](repeating_timer *t) {
                reinterpret_cast<pulseCounter *>(t->user_data)->onSecondPassed();
                return true;
            },
            this, &secondTimer);
        counting = true;
    }
}

void pulseCounter::pauseCounting() {
    if (counting) {
        gpio_remove_raw_irq_handler(pulsePin, pulseCallback);
        gpio_set_irq_enabled(pulsePin, irqEgdeLowEventMask, false);
        cancel_repeating_timer(&secondTimer);
        counting = false;
    }
}

bool pulseCounter::isCounting() {
    return counting;
}

inline void pulseCounter::onPulse() {
    ++currentSecondCount;
}

void pulseCounter::onSecondPassed() {
    lastPeriod.pop_front();
    lastPeriod.push_back(currentSecondCount);
    totalCount += currentSecondCount;
    currentSecondCount = 0;
    if (auto tmp = view.lock())
        tmp->updateMeasurement();
}

void pulseCounter::setView(const std::shared_ptr<iPulseCounterView> &ref) {
    view = ref;
}

unsigned pulseCounter::getCountsInLastPeriod() {
    if (counting) {
        return std::accumulate(lastPeriod.begin(), lastPeriod.end(), 0);
    } else {
        return 0;
    }
}

unsigned pulseCounter::getMeasurementTime() {
    return measurementTime;
}

void pulseCounter::setMeasurementTime(unsigned newTime) {
    lastPeriod = std::deque<unsigned>(newTime, 0);
    measurementTime = newTime;
}

unsigned long pulseCounter::getTotalCount() {
    return totalCount;
}