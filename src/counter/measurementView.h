#ifndef MEASUREMENTVIEW_H
#define MEASUREMENTVIEW_H

#include <memory>
#include <string>

#include "../iView.h"
#include "iPulseCounterView.h"
#include "iUnitListener.h"
class LiquidCrystal_I2C;
class unitConverter;
class iController;
class measurementView : public iView, public iPulseCounterView, public iUnitListener {
    std::shared_ptr<LiquidCrystal_I2C> lcd;
    std::weak_ptr<unitConverter> data;
    std::shared_ptr<iController> controller;
    unsigned short row;
    unsigned short previouslyDisplayedValueLength;
    unsigned short leftMargin;
    bool measurementToUpdate;
    bool enabled;

    void clean();
    std::string cutMeasurementValueToDisplay(float val);
    void display();

   public:
    measurementView(const std::shared_ptr<LiquidCrystal_I2C>& lcd, const std::shared_ptr<unitConverter>& data, unsigned short rowToDisplay, const std::shared_ptr<iController>& controller);
    void mainLoop();
    virtual void updateMeasurement() override;
    virtual void onUnitChange() override;
    virtual void enable() override;
    virtual void disable() override;
    virtual std::shared_ptr<iController> getController() override;

    virtual ~measurementView() noexcept override;
};

#endif