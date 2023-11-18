#include <stdio.h>

#include <memory>

#include "backlightSetting.h"
#include "displayManager.h"
#include "mainController.h"
#include "measurementTimeSetting.h"
#include "measurementView.h"
#include "measurementViewController.h"
#include "pico/stdlib.h"
#include "pulseCounter.h"
#include "settingsModel.h"
#include "settingsView.h"
#include "settingsViewController.h"
#include "stopwatchModel.h"
#include "stopwatchView.h"
#include "stopwatchViewController.h"
#include "unitConverter.h"
#include "unitSetting.h"
#define SBM20_CONVERSION_RATE 0.0056
#define viewChangebutton 15
#define geigerPin 12
#define button1 14
#define button2 13

int main() {
    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true);  // enable interrupts with callbacks on core

    std::shared_ptr<displayManager> manager(new displayManager());
    std::shared_ptr<mainController> controller(new mainController(viewChangebutton, manager));
    manager->setController(controller);
    controller->addButton<viewChangebutton>();
    controller->addButton<button1>();
    controller->addButton<button2>();

    bool led = false;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    std::shared_ptr<LiquidCrystal_I2C>
        lcd(new LiquidCrystal_I2C(16, 17, 16, 2, 0U, 0x27));
    lcd->backlight();
    lcd->setCursor(0, 0);
    lcd->printStr("test");
    sleep_ms(100);

    std::shared_ptr<pulseCounter> counter{new pulseCounter(15, geigerPin)};
    counter->startCounting();
    std::shared_ptr<unitConverter> converter{new unitConverter{SBM20_CONVERSION_RATE, counter}};
    converter->setUnit(unitConverter::usvh);

    std::shared_ptr<measurementView> view(new measurementView(lcd, converter, 0, std::shared_ptr<iController>(new measurementViewController())));
    counter->setView(view);
    converter->setUnitListener(view);
    manager->addView(view);

    std::shared_ptr<stopwatchModel> stopwatch(new stopwatchModel());
    std::shared_ptr<stopwatchView> stopwView(new stopwatchView(lcd, stopwatch, std::shared_ptr<iController>(new stopwatchViewController(stopwatch, button1, button2)), 0));
    manager->addView(stopwView);

    std::shared_ptr<settingsModel> settings(new settingsModel());
    settings->addSetting(std::shared_ptr<setting>(new measurementTimeSetting(counter)));
    settings->addSetting(std::shared_ptr<setting>(new unitSetting(converter)));
    settings->addSetting(std::shared_ptr<setting>(new backlightSetting(lcd)));

    std::shared_ptr<settingsView> sView(new settingsView(lcd, settings, 0, std::shared_ptr<iController>(new settingsViewController(settings, button1, button2))));
    settings->setView(sView);
    manager->addView(sView);

    while (true) {
        sleep_ms(100);
        gpio_put(PICO_DEFAULT_LED_PIN, led);
        led = !led;
        controller->mainLoop();
        view->mainLoop();
        stopwView->mainLoop();
    }
}