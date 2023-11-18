#ifndef STOPWATCHVIEW_H
#define STOPWATCHVIEW_H
#include <memory>

#include "LCDI2C/LiquidCrystal_I2C.h"
#include "iView.h"
#include "stopwatchModel.h"
class stopwatchView : public iView {
    std::shared_ptr<LiquidCrystal_I2C> lcd;
    std::weak_ptr<stopwatchModel> stopwatch;
    std::shared_ptr<iController> controller;
    time previouslyDisplayedTime;
    unsigned margin;
    unsigned displayRow : 31;
    bool isEnabled : 1;

    void clean();
    void display();
    void signalizeError();
    static std::string convertToDisplay(unsigned, unsigned);

   public:
    stopwatchView(const std::shared_ptr<LiquidCrystal_I2C>& lcd, const std::shared_ptr<stopwatchModel>& stopwatch, const std::shared_ptr<iController>& controller, unsigned row);
    void mainLoop();
    virtual void enable() override;
    virtual void disable() override;
    virtual std::shared_ptr<iController> getController() override;
    ~stopwatchView() = default;
};

#endif