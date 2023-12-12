#include "measurementTimeSetting.h"

#include <algorithm>
#include <iterator>

#include "../counter/pulseCounter.h"
measurementTimeSetting::measurementTimeSetting(const std::shared_ptr<pulseCounter>& ref) : counter(ref) {
}

void measurementTimeSetting::changeValue() {
    if (auto tmp = counter.lock()) {
        unsigned index = std::distance(measurementTimes.begin(), std::find(measurementTimes.begin(), measurementTimes.end(), tmp->getMeasurementTime()));
        index += 1;
        index %= measurementTimes.size();
        tmp->setMeasurementTime(measurementTimes[index]);
    }
}

std::string measurementTimeSetting::settingName() {
    return std::string("meas. time");
}

std::string measurementTimeSetting::settingValue() {
    if (auto tmp = counter.lock()) {
        return std::to_string(tmp->getMeasurementTime());
    } else {
        return std::string("err");
    }
}