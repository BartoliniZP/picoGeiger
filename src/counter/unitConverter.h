#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H
#include <memory>
class pulseCounter;
class iUnitListener;
class unitConverter {
   public:
    enum unit {
        usvh,
        cpm,
        totalCount,
        cps,
        NUMBER_OF_UNITS
    };

    inline static const char* unitStrings[4]{"uSv/h", "cpm", "total", "cps"};
    unitConverter(float conversionTouSvRate, const std::shared_ptr<pulseCounter>& counter);
    const char* getSelectedUnitName();
    unit getSelectedUnit();
    void setUnit(unit);
    float getSelectedUnitValue();
    void setUnitListener(const std::shared_ptr<iUnitListener>& listener);

   private:
    unit selectedUnit;
    float conversionRate;
    std::weak_ptr<pulseCounter> counter;
    std::weak_ptr<iUnitListener> listener;
};

#endif