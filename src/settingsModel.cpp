#include "settingsModel.h"

void settingsModel::addSetting(const std::shared_ptr<setting>& sett) {
    settings.push_back(sett);
}

void settingsModel::changeActiveSetting() {
    if (settings.size() == 0)
        return;
    activeSettingIndex += 1;
    activeSettingIndex = activeSettingIndex % settings.size();

    if (auto tmp = view.lock()) {
        tmp->onActiveSettingChange();
    }
}

void settingsModel::changeActiveSettingValue() {
    if (settings.size() == 0)
        return;
    settings[activeSettingIndex]->changeValue();

    if (auto tmp = view.lock()) {
        tmp->onSettingValueChange();
    }
}

std::shared_ptr<setting> settingsModel::getActiveSetting() {
    if (settings.size() == 0)
        return std::shared_ptr<setting>();
    return settings[activeSettingIndex];
}

void settingsModel::setView(const std::shared_ptr<iSettingsView>& ref) {
    view = ref;
}