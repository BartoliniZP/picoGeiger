#ifndef BACKLIGHTSETTING_H
#define BACKLIGHTSETTING_H
#include <memory>
#include <string>

#include "LCDI2C/LiquidCrystal_I2C.h"
#include "setting.h"
class backlightSetting : public setting {
    std::weak_ptr<LiquidCrystal_I2C> lcd;

   public:
    backlightSetting(const std::shared_ptr<LiquidCrystal_I2C>&);
    void changeValue() override;
    std::string settingName() override;
    std::string settingValue() override;
    ~backlightSetting() noexcept = default;
};

#endif