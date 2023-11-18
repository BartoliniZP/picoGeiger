#include "settingsView.h"

#include "../LCDI2C/LiquidCrystal_I2C.h"
#include "setting.h"
#include "settingsModel.h"
#include "settingsViewController.h"
settingsView::settingsView(const std::shared_ptr<LiquidCrystal_I2C> &lcd_ref, const std::shared_ptr<settingsModel> &data_ref, unsigned short rowIndex, const std::shared_ptr<iController> &controller) : lcd(lcd_ref), data(data_ref), controller(controller), settingValueFirstLetterPosition(0), displayRow(rowIndex), isEnabled(false) {
}

void settingsView::enable() {
    isEnabled = true;
    displayAtCenter();
}

void settingsView::disable() {
    if (isEnabled)
        clean();
    isEnabled = false;
}

void settingsView::clean() {
    if (!isEnabled)
        return;
    lcd->setCursor(0, displayRow);
    lcd->printStr(std::string(lcd->getColumns(), ' ').c_str());
}

settingsView::~settingsView() noexcept {
    if (isEnabled) clean();
}

std::shared_ptr<iController> settingsView::getController() {
    return controller;
}

void settingsView::displayAtCenter() {
    if (!isEnabled)
        return;

    clean();

    if (auto tmp = data.lock()) {
        if (auto setting = tmp->getActiveSetting()) {
            std::string name = setting->settingName();
            std::string val = setting->settingValue();
            unsigned margin = (lcd->getColumns() - name.size() - val.size() - 2) / 2;
            // 2 for ": " between name and value
            settingValueFirstLetterPosition = (margin + setting->settingName().size() + 2);
            lcd->setCursor(margin, displayRow);
            lcd->printStr(setting->settingName().c_str());
            if (setting->settingName().length() != 0) {
                lcd->printStr(": ");
            }
            lcd->printStr(setting->settingValue().c_str());
        }
    }
}

void settingsView::onActiveSettingChange() {
    displayAtCenter();
}

void settingsView::onSettingValueChange() {
    if (!isEnabled)
        return;
    if (auto tmp = data.lock()) {
        if (auto setting = tmp->getActiveSetting()) {
            lcd->setCursor(settingValueFirstLetterPosition, displayRow);
            lcd->printStr(std::string(lcd->getColumns() - settingValueFirstLetterPosition, ' ').c_str());
            lcd->setCursor(settingValueFirstLetterPosition, displayRow);
            lcd->printStr(setting->settingValue().c_str());
        } else {
            lcd->setCursor(0, displayRow);
            lcd->printStr(std::string(lcd->getColumns(), ' ').c_str());
        }
    }
}