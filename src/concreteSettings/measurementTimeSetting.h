#ifndef MTSETTING_H
#define MTSETTING_H
#include <memory>
#include <string>

#include "../settingsMVC/setting.h"

class pulseCounter;
class measurementTimeSetting : public setting {
    std::weak_ptr<pulseCounter> counter;

   public:
    measurementTimeSetting(const std::shared_ptr<pulseCounter>&);
    void changeValue() override;
    std::string settingName() override;
    std::string settingValue() override;
    ~measurementTimeSetting() noexcept = default;
};

#endif