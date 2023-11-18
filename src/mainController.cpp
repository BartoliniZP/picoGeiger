#include "mainController.h"
#include "iController.h"
#include "displayManager.h"
#define irqEgdeLowEventMask 0b100

#include "utils/callableWrapper.hpp"
mainController::mainController(unsigned viewChangeButtonID, const std::shared_ptr<displayManager>& manager) : activeController(), manager(manager), callbacks(), buttonPressesToHandle(), viewChangeButtonID(viewChangeButtonID) {
}

void mainController::setActiveController(const std::shared_ptr<iController>& ref) {
    activeController = ref;
}

void mainController::buttonPressed(unsigned id) {
    if (callbacks.find(id) != callbacks.end()) {
        buttonPressesToHandle[id] = true;
    }
}

void mainController::mainLoop() {
    for (auto& toHandle : buttonPressesToHandle) {
        if (toHandle.second) {
            if (toHandle.first == viewChangeButtonID) {
                if (auto tmp = manager.lock()) {
                    tmp->changeView();
                }
            } else {
                if (activeController)
                    activeController->onButton(toHandle.first);
            }
            toHandle.second = false;
        }
    }
}

mainController::~mainController() {
    for (auto& callback : callbacks) {
        gpio_remove_raw_irq_handler(callback.first, callback.second);
        gpio_set_irq_enabled(callback.first, irqEgdeLowEventMask, false);
        gpio_disable_pulls(callback.first);
        gpio_deinit(callback.first);
    }
}