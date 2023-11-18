#ifndef BACKLIGHTSETTING_H
#define BACKLIGHTSETTING_H
#include <memory>
#include <string>

#include "../settingsMVC/setting.h"

class LiquidCrystal_I2C;
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