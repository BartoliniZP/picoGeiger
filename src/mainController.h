#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <map>
#include <memory>

#include "utils/callableWrapper.hpp"
#define irqEgdeLowEventMask 0b100

#include "pico/stdlib.h"
class iController;
class displayManager;
class mainController {
    std::shared_ptr<iController> activeController;
    std::weak_ptr<displayManager> manager;
    std::map<unsigned, irq_handler_t> callbacks;
    std::map<unsigned, bool> buttonPressesToHandle;
    unsigned viewChangeButtonID;

   public:
    mainController(unsigned viewChangeButtonID, const std::shared_ptr<displayManager>& manager);
    ~mainController();
    void buttonPressed(unsigned id);
    void mainLoop();
    void setActiveController(const std::shared_ptr<iController>& ref);
    template <unsigned id>
    void addButton();
};

template <unsigned buttonPin>
void mainController::addButton() {
    buttonPressesToHandle[buttonPin] = false;
    gpio_init(buttonPin);
    gpio_set_dir(buttonPin, GPIO_IN);
    gpio_pull_down(buttonPin);
    gpio_set_irq_enabled(buttonPin, irqEgdeLowEventMask, true);
    callbacks[buttonPin] = callableWrapper<buttonPin>([this, bp = buttonPin]() {  // as callable wrapper
        if (gpio_get_irq_event_mask(bp) & irqEgdeLowEventMask) {
            gpio_acknowledge_irq(bp, irqEgdeLowEventMask);
            this->buttonPressed(bp);
        }
    });
    gpio_add_raw_irq_handler(buttonPin, callbacks[buttonPin]);
}

#endif