#ifndef IPULSECOUNTERVIEW_H
#define IPULSECOUNTERVIEW_H

struct iPulseCounterView {
    virtual void updateMeasurement() = 0;  // this function is called on timer callback, it should be lightweight e.g. only annotating that measurement should be changed, real actions about measurement changes should happen in main loop
    virtual ~iPulseCounterView() noexcept = default;
};

#endif