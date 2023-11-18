#ifndef SETTINGSVIEWCONTROLLER_H
#define SETTINGSVIEWCONTROLLER_H
#include <memory>

#include "iController.h"
#include "settingsModel.h"
class settingsViewController : public iController {
    std::weak_ptr<settingsModel> settings;
    unsigned changeSettingButtonID;
    unsigned changeSettingValueButtonID;

   public:
    settingsViewController(const std::shared_ptr<settingsModel>& settings, unsigned changeSettingButtonID, unsigned changeSettingValueButtonID);
    void onButton(unsigned buttonID) override;
};

#endif