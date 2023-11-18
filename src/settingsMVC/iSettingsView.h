#ifndef ISETTINGSVIEW_H
#define ISETTINGSVIEW_H

struct iSettingsView {
    virtual void onActiveSettingChange() = 0;
    virtual void onSettingValueChange() = 0;
    ~iSettingsView() noexcept = default;
};

#endif