#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H
#include <memory>
#include <vector>

#include "setting.h"
class settingsModel {
   public:
    struct iSettingsView {
        virtual void onActiveSettingChange() = 0;
        virtual void onSettingValueChange() = 0;
        ~iSettingsView() noexcept = default;
    };

   private:
    std::vector<std::shared_ptr<setting>> settings;
    unsigned int activeSettingIndex;
    std::weak_ptr<iSettingsView> view;

   public:
    settingsModel() = default;
    void addSetting(const std::shared_ptr<setting> &);
    void changeActiveSetting();
    void changeActiveSettingValue();
    std::shared_ptr<setting> getActiveSetting();
    void setView(const std::shared_ptr<iSettingsView> &);
};

#endif