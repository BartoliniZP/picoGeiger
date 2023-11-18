#include "displayManager.h"

#include "iView.h"
#include "mainController.h"

void displayManager::setController(const std::shared_ptr<mainController> &controllerRef) {
    controller = controllerRef;
}

void displayManager::addView(const std::shared_ptr<iView> &viewRef) {
    views.push_back(viewRef);
    if (views.size() == 1) {
        views[0]->enable();
        if (auto tmp = controller.lock()) {
            tmp->setActiveController(views[0]->getController());
        }
        activeViewIndex = 0;
    }
}

void displayManager::changeView() {
    if (views.size() != 0) {
        views[activeViewIndex]->disable();
        activeViewIndex = (activeViewIndex + 1) % views.size();
        views[activeViewIndex]->enable();
        if (auto tmp = controller.lock()) {
            std::shared_ptr<iController> a{views[activeViewIndex]->getController()};
            tmp->setActiveController(a);
        }
    }
}