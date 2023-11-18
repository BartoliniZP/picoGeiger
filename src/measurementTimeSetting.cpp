#include "measurementTimeSetting.h"

measurementTimeSetting::measurementTimeSetting(const std::shared_ptr<pulseCounter>& ref) : counter(ref) {
}

void measurementTimeSetting::changeValue() {
    if (auto tmp = counter.lock()) {
        unsigned current = tmp->getMeasurementTime();
        if (current == 15)
            tmp->setMeasurementTime(30);
        else if (current == 30)
            tmp->setMeasurementTime(60);
        else
            tmp->setMeasurementTime(15);
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