#include <stdio.h>

#include <memory>

#include "displayManager.h"
#include "mainController.h"
#include "measurementView.h"
#include "pico/stdlib.h"
#include "pulseCounter.h"
#include "unitConverter.h"
#define SBM20_CONVERSION_RATE 0.0056
#define buttonPin 14
#define geigerPin 16

int main() {
    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true);  // enable interrupts with callbacks on core

    std::shared_ptr<displayManager> manager(new displayManager());
    std::shared_ptr<mainController> controller(new mainController(buttonPin, manager));
    manager->setController(controller);
    controller->addButton<buttonPin>();
    controller->addButton<15>();

    bool led = false;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    std::shared_ptr<pulseCounter> counter{new pulseCounter(15, geigerPin)};
    counter->startCounting();

    std::shared_ptr<unitConverter> converter{new unitConverter{SBM20_CONVERSION_RATE, counter}};
    converter->setUnit(unitConverter::usvh);

    std::shared_ptr<LiquidCrystal_I2C> lcd(new LiquidCrystal_I2C(16, 2, 0U, 0x27));
    lcd->backlight();
    lcd->setCursor(0, 0);
    lcd->printStr("test");
    sleep_ms(100);

    std::shared_ptr<measurementView> view(new measurementView(lcd, converter, 0));

    counter->setView(view);
    converter->setUnitListener(view);
    manager->addView(view);

    while (true) {
        sleep_ms(1000);
        gpio_put(PICO_DEFAULT_LED_PIN, led);
        led = !led;
        controller->mainLoop();
        view->mainLoop();
    }
}