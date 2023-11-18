#include "stopwatchView.h"

#include <cmath>
#include <string>
stopwatchView::stopwatchView(const std::shared_ptr<LiquidCrystal_I2C>& lcd, const std::shared_ptr<stopwatchModel>& stopwatch, const std::shared_ptr<iController>& controller, unsigned row) : lcd(lcd), stopwatch(stopwatch), controller(controller), previouslyDisplayedTime{0, 0, 0}, margin(0), displayRow(row), isEnabled(false) {
}

void stopwatchView::enable() {
    isEnabled = true;
    display();
}

void stopwatchView::disable() {
    if (isEnabled) clean();
    isEnabled = false;
}

std::shared_ptr<iController> stopwatchView::getController() {
    return controller;
}

void stopwatchView::clean() {
    if (!isEnabled)
        return;
    lcd->setCursor(0, displayRow);
    lcd->printStr(std::string(lcd->getColumns(), ' ').c_str());
}

static unsigned decimalDigitsOfNumber(unsigned number) {
    return (static_cast<unsigned>(log10(number)) + 1);
}

std::string stopwatchView::convertToDisplay(unsigned val, unsigned len) {
    if (val == 0)
        return std::string(len, '0');
    else if (val < pow(10, len - 1))
        return std::string(len - decimalDigitsOfNumber(val), '0') + std::to_string(val);
    else
        return std::to_string(val);
}

void stopwatchView::display() {
    if (!isEnabled) {
        return;
    }
    clean();
    if (auto tmp = stopwatch.lock()) {
        std::string toDisplay{};
        previouslyDisplayedTime = tmp->getCurrentMeasure();
        toDisplay += convertToDisplay(previouslyDisplayedTime.minutes, std::max(decimalDigitsOfNumber(previouslyDisplayedTime.minutes), 2u));
        toDisplay += ':';
        toDisplay += convertToDisplay(previouslyDisplayedTime.seconds, 2);
        toDisplay += ':';
        toDisplay += convertToDisplay(previouslyDisplayedTime.milliseconds, 3);
        margin = (lcd->getColumns() - toDisplay.length()) / 2;
        lcd->setCursor(margin, displayRow);
        lcd->printStr(toDisplay.c_str());

    } else {
        signalizeError();
    }
}

void stopwatchView::signalizeError() {
    lcd->setCursor(0, displayRow);
    lcd->printStr("err");
}

void stopwatchView::mainLoop() {
    if (!isEnabled) return;

    if (auto tmp = stopwatch.lock()) {
        time t = tmp->getCurrentMeasure();
        if (decimalDigitsOfNumber(t.minutes) > decimalDigitsOfNumber(previouslyDisplayedTime.minutes))
            display();
        else {
            unsigned minutesSize = std::max(decimalDigitsOfNumber(t.minutes), 2u);
            if (t.minutes != previouslyDisplayedTime.minutes) {
                lcd->setCursor(margin, displayRow);
                lcd->printStr(convertToDisplay(t.minutes, minutesSize).c_str());
            }
            if (t.seconds != previouslyDisplayedTime.seconds) {
                lcd->setCursor(margin + minutesSize + 1, displayRow);
                lcd->printStr(convertToDisplay(t.seconds, 2).c_str());
            }
            if (t.milliseconds != previouslyDisplayedTime.milliseconds) {
                lcd->setCursor(margin + minutesSize + 1 + 2 + 1, displayRow);
                lcd->printStr(convertToDisplay(t.milliseconds, 3).c_str());
            }
            previouslyDisplayedTime = t;
        }
    } else {
        signalizeError();
    }
}