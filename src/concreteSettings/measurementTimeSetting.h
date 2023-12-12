#ifndef MTSETTING_H
#define MTSETTING_H
#include <array>
#include <memory>
#include <string>

#include "../settingsMVC/setting.h"

class pulseCounter;
class measurementTimeSetting : public setting {
    std::weak_ptr<pulseCounter> counter;
    constexpr inline static std::array<unsigned, 3> measurementTimes{15, 30, 60};

   public:
    measurementTimeSetting(const std::shared_ptr<pulseCounter>&);
    void changeValue() override;
    std::string settingName() override;
    std::string settingValue() override;
    ~measurementTimeSetting() noexcept = default;
};

#endif