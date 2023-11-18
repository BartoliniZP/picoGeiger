#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <memory>

#include "LCDI2C/LiquidCrystal_I2C.h"
#include "iView.h"
#include "settingsModel.h"
class settingsView : public iView, public settingsModel::iSettingsView {
    std::shared_ptr<LiquidCrystal_I2C> lcd;
    std::weak_ptr<settingsModel> data;
    std::shared_ptr<iController> controller;
    unsigned short settingValueFirstLetterPosition;
    unsigned short displayRow : 15;
    bool isEnabled : 1;
    void displayAtCenter();
    void clean();

   public:
    settingsView(const std::shared_ptr<LiquidCrystal_I2C> &lcd_ref, const std::shared_ptr<settingsModel> &data_ref, unsigned short rowIndex, const std::shared_ptr<iController> &controller);
    void onActiveSettingChange() override;
    void onSettingValueChange() override;
    void enable() override;
    void disable() override;
    std::shared_ptr<iController> getController() override;
    ~settingsView() noexcept override;
};

#endif