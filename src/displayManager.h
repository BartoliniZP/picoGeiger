#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include <memory>
#include <vector>

#include "iView.h"

class mainController;
class displayManager {
    std::vector<std::shared_ptr<iView>> views;
    std::weak_ptr<mainController> controller;
    unsigned int activeViewIndex;

   public:
    displayManager() = default;
    void setController(const std::shared_ptr<mainController> &controller);
    void addView(const std::shared_ptr<iView> &view);
    void changeView();
    ~displayManager() = default;
};

#endif