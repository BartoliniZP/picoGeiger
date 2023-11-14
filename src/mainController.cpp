#include "mainController.h"

#include "displayManager.h"
#define irqEgdeLowEventMask 0b100

#include "utils/callableWrapper.hpp"
mainController::mainController(unsigned viewChangeButtonID, const std::shared_ptr<displayManager>& manager) : activeController(), manager(manager), callbacks(), buttonPressesToHandle(), viewChangeButtonID(viewChangeButtonID) {
    addButton(viewChangeButtonID);
}

void mainController::addButton(unsigned buttonPin) {
    buttonPressesToHandle[buttonPin] = false;
    gpio_init(buttonPin);
    gpio_set_dir(buttonPin, GPIO_IN);
    gpio_pull_down(buttonPin);
    gpio_set_irq_enabled(buttonPin, irqEgdeLowEventMask, true);
    callbacks[buttonPin] = wrapper([this, buttonPin]() { 
            if(gpio_get_irq_event_mask(buttonPin)&irqEgdeLowEventMask) {
            gpio_acknowledge_irq(buttonPin, irqEgdeLowEventMask); 
            this->buttonPressed(buttonPin);
            } });
    gpio_add_raw_irq_handler(buttonPin, callbacks[buttonPin]);
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