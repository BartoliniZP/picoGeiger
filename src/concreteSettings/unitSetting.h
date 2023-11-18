#ifndef UNITSETTING_H
#define UNITSETTING_H
#include <memory>
#include <string>

#include "../settingsMVC/setting.h"
class unitConverter;
class unitSetting : public setting {
    std::weak_ptr<unitConverter> unitData;

   public:
    unitSetting(const std::shared_ptr<unitConverter>&);
    void changeValue() override;
    std::string settingName() override;
    std::string settingValue() override;
    ~unitSetting() noexcept = default;
};

#endif