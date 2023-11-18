#include "stopwatchModel.h"

#include "../utils/time.h"
void stopwatchModel::start() {
    if (isGoing) return;

    if (startPoint == 0) {
        startPoint = get_absolute_time()._private_us_since_boot;
    } else {
        startPoint = get_absolute_time()._private_us_since_boot - (pausePoint - startPoint);
        pausePoint = 0;
    }

    isGoing = true;
}

void stopwatchModel::pause() {
    pausePoint = get_absolute_time()._private_us_since_boot;
    isGoing = false;
}

void stopwatchModel::reset() {
    isGoing = false;
    startPoint = 0;
    pausePoint = 0;
}

time stopwatchModel::getCurrentMeasure() {
    uint64_t timeFromStart = 0;
    if (isGoing) {
        timeFromStart = get_absolute_time()._private_us_since_boot - startPoint;
    } else if (pausePoint != 0) {
        timeFromStart = pausePoint - startPoint;
    }
    return convertUStoTime(timeFromStart);
}

time stopwatchModel::convertUStoTime(uint64_t us) {
    time toReturn{0, 0, 0};
    toReturn.milliseconds = (us % 1'000'000) / 1000;
    toReturn.seconds = (us / 1'000'000) % 60;
    toReturn.minutes = (us / 1'000'000) / 60;
    return toReturn;
}

bool stopwatchModel::isRunning() {
    return isGoing;
}