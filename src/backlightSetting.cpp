#include "backlightSetting.h"

backlightSetting::backlightSetting(const std::shared_ptr<LiquidCrystal_I2C>& ref) : lcd(ref) {
}

void backlightSetting::changeValue() {
    if (auto tmp = lcd.lock()) {
        if (tmp->getBacklightValue()) {
            tmp->noBacklight();
        } else {
            tmp->backlight();
        }
    }
}

std::string backlightSetting::settingName() {
    return std::string("backlight");
}

std::string backlightSetting::settingValue() {
    if (auto tmp = lcd.lock()) {
        return tmp->getBacklightValue() ? std::string("on") : std::string("off");
    } else {
        return std::string("err");
    }
}