#include "unitConverter.h"

#include "pulseCounter.h"

unitConverter::unitConverter(float conversionTouSvRate, const std::shared_ptr<pulseCounter>& counter) : selectedUnit(cpm), conversionRate(conversionTouSvRate), counter(counter) {
}

const char* unitConverter::getSelectedUnitName() {
    return unitStrings[selectedUnit];
}

unitConverter::unit unitConverter::getSelectedUnit() {
    return selectedUnit;
}

void unitConverter::setUnit(unit u) {
    selectedUnit = u;
    if (auto tmp = listener.lock()) {
        tmp->onUnitChange();
    }
}

float unitConverter::getSelectedUnitValue() {
    if (auto tmp = counter.lock()) {
        if (selectedUnit == cpm) {
            float ret = static_cast<float>(tmp->getCountsInLastPeriod()) * (60.0f / static_cast<float>(tmp->getMeasurementTime()));
            return ret;
        } else if (selectedUnit == cps) {
            float ret = static_cast<float>(tmp->getCountsInLastPeriod()) / static_cast<float>(tmp->getMeasurementTime());
            return ret;
        } else if (selectedUnit == usvh) {
            float ret = conversionRate * static_cast<float>(tmp->getCountsInLastPeriod()) * (60.0f / static_cast<float>(tmp->getMeasurementTime()));
            return ret;
        } else if (selectedUnit == totalCount) {
            return tmp->getTotalCount();
        }
    } else {
        return 0.0f;
    }
}

void unitConverter::setUnitListener(const std::shared_ptr<iUnitListener>& listener) {
    this->listener = listener;
}