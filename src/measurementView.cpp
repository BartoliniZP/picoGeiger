#include "measurementView.h"

#include <cmath>

#include "measurementViewController.h"
measurementView::measurementView(const std::shared_ptr<LiquidCrystal_I2C>& lcd, const std::shared_ptr<unitConverter>& data, unsigned short rowToDisplay, const std::shared_ptr<iController>& controller) : lcd(lcd), data(data), controller(controller), row(rowToDisplay), previouslyDisplayedValueLength(0), leftMargin(0), measurementToUpdate(false), enabled(false) {
}

void measurementView::mainLoop() {  // only refresh value if needed
    if (measurementToUpdate && enabled) {
        if (auto tmp = data.lock()) {
            std::string valueToDisplay = cutMeasurementValueToDisplay(tmp->getSelectedUnitValue());
            if (valueToDisplay.length() == previouslyDisplayedValueLength) {
                lcd->setCursor(leftMargin, row);
                lcd->printStr(valueToDisplay.c_str());
            } else {
                display();
            }
        }
        measurementToUpdate = false;
    }
}

std::string measurementView::cutMeasurementValueToDisplay(float val) {
    std::string toReturn;
    if (val < 100.0) {
        toReturn = std::to_string(val).substr(0, 4);
    } else {
        toReturn = std::to_string(static_cast<unsigned>(val));
    }
    return toReturn;
}

void measurementView::display() {
    if (!enabled) return;
    if (auto tmp = data.lock()) {
        clean();
        std::string toDisplay{};
        toDisplay = cutMeasurementValueToDisplay(tmp->getSelectedUnitValue());
        previouslyDisplayedValueLength = toDisplay.length();
        toDisplay += ' ';
        toDisplay += tmp->getSelectedUnitName();
        leftMargin = std::floor((static_cast<float>(lcd->getColumns()) - static_cast<float>(toDisplay.length())) / 2.0f);
        lcd->setCursor(leftMargin, row);
        lcd->printStr(toDisplay.c_str());
    }
}

measurementView::~measurementView() noexcept {
    if (enabled) clean();
}

void measurementView::clean() {
    if (!enabled) return;
    lcd->setCursor(0, row);
    lcd->printStr(std::string(lcd->getColumns(), ' ').c_str());
}

void measurementView::onUnitChange() {
    if (enabled)
        display();
}

void measurementView::enable() {
    enabled = true;
    display();
}

void measurementView::disable() {
    if (enabled) clean();
    enabled = false;
}

void measurementView::updateMeasurement() {
    measurementToUpdate = true;
}

std::shared_ptr<iController> measurementView::getController() {
    return controller;
}
