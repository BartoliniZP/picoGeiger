#ifndef STOPWATCHVIEWCONTROLLER_H
#define STOPWATCHVIEWCONTROLLER_H
#include <memory>

#include "iController.h"
#include "stopwatchModel.h"
class stopwatchViewController : public iController {
    std::weak_ptr<stopwatchModel> stopwatch;
    unsigned pauseButtonID;
    unsigned resetButtonID;

   public:
    stopwatchViewController(const std::shared_ptr<stopwatchModel>& stopwatch, unsigned pauseButtonID, unsigned resetButtonID);
    void onButton(unsigned buttonID) override;
};

#endif