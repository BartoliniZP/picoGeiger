#ifndef MEASUREMENTVIEWCONTROLLER_H
#define MEASUREMENTVIEWCONTROLLER_H

#include "iController.h"
class measurementViewController : public iController {
   public:
    virtual void onButton(unsigned buttonID) override;
    virtual ~measurementViewController() noexcept = default;
};

#endif