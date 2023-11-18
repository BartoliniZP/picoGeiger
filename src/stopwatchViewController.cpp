#include "stopwatchViewController.h"

stopwatchViewController::stopwatchViewController(const std::shared_ptr<stopwatchModel>& stopwatch, unsigned pauseButtonID, unsigned resetButtonID) : stopwatch(stopwatch), pauseButtonID(pauseButtonID), resetButtonID(resetButtonID) {
}

void stopwatchViewController::onButton(unsigned buttonID) {
    if (auto tmp = stopwatch.lock()) {
        if (buttonID == resetButtonID) {
            tmp->reset();
        } else if (buttonID == pauseButtonID) {
            if (tmp->isRunning()) {
                tmp->pause();
            } else {
                tmp->start();
            }
        }
    }
}