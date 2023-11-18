#ifndef IUNITLISTENER_H
#define IUNITLISTENER_H

struct iUnitListener {
    virtual void onUnitChange() = 0;
    virtual ~iUnitListener() noexcept = default;
};

#endif