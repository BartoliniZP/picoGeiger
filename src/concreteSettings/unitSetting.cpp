#include "unitSetting.h"

#include "../counter/unitConverter.h"
unitSetting::unitSetting(const std::shared_ptr<unitConverter>& ref) : unitData(ref) {
}

void unitSetting::changeValue() {
    if (auto tmp = unitData.lock()) {
        unitConverter::unit current = tmp->getSelectedUnit();
        if (current == unitConverter::usvh)
            tmp->setUnit(unitConverter::cpm);
        else if (current == unitConverter::cpm)
            tmp->setUnit(unitConverter::cps);
        else if (current == unitConverter::cps)
            tmp->setUnit(unitConverter::totalCount);
        else if (current == unitConverter::totalCount)
            tmp->setUnit(unitConverter::usvh);
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