#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <map>
#include <memory>

#include "iController.h"
#include "pico/stdlib.h"
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
    void addButton(unsigned pin);
};

#endif