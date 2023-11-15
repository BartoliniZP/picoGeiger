#ifndef MEASUREMENTVIEW_H
#define MEASUREMENTVIEW_H
#include <memory>
#include <string>

#include "LCDI2C/LiquidCrystal_I2C.h"
#include "iController.h"
#include "iView.h"
#include "pulseCounter.h"
#include "unitConverter.h"

class measurementView : public iView, public pulseCounter::iPulseCounterView, public unitConverter::iUnitListener {
    std::shared_ptr<LiquidCrystal_I2C> lcd;
    std::weak_ptr<unitConverter> data;
    unsigned short row;
    unsigned short previouslyDisplayedValueLength;
    unsigned short leftMargin;
    bool measurementToUpdate;
    bool enabled;

    void clean();
    std::string cutMeasurementValueToDisplay(float val);
    void display();

   public:
    measurementView(const std::shared_ptr<LiquidCrystal_I2C>& lcd, const std::shared_ptr<unitConverter>& data, unsigned short rowToDisplay);
    void mainLoop();
    virtual void updateMeasurement() override;
    virtual void onUnitChange() override;
    virtual void enable() override;
    virtual void disable() override;
    virtual std::shared_ptr<iController> getController() override;

    virtual ~measurementView() noexcept override;
};

#endif