#include "unitSetting.h"

#include "../counter/unitConverter.h"
unitSetting::unitSetting(const std::shared_ptr<unitConverter>& ref) : unitData(ref) {
}

void unitSetting::changeValue() {
    if (auto tmp = unitData.lock()) {
        tmp->setUnit(unitConverter::unit((static_cast<int>(tmp->getSelectedUnit()) + 1) % unitConverter::unit::NUMBER_OF_UNITS));
    }
}

std::string unitSetting::settingName() {
    return std::string("unit");
}

std::string unitSetting::settingValue() {
    if (auto tmp = unitData.lock()) {
        return tmp->getSelectedUnitName();
    } else {
        return std::string("err");
    }
}