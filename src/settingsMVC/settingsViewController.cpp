#include "settingsViewController.h"

#include "settingsModel.h"
settingsViewController::settingsViewController(const std::shared_ptr<settingsModel>& settings, unsigned changeSettingButtonID, unsigned changeSettingValueButtonID) : settings(settings), changeSettingButtonID(changeSettingButtonID), changeSettingValueButtonID(changeSettingValueButtonID) {
}

void settingsViewController::onButton(unsigned buttonID) {
    if (auto tmp = settings.lock()) {
        if (buttonID == changeSettingButtonID) {
            tmp->changeActiveSetting();
        } else if (buttonID == changeSettingValueButtonID) {
            tmp->changeActiveSettingValue();
        }
    }
}