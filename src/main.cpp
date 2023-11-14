#include <stdio.h>

#include <memory>

#include "displayManager.h"
#include "mainController.h"
#include "pico/stdlib.h"
#include "pulseCounter.h"
#define buttonPin 17
#define geigerPin 16

int main() {
    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true);  // enable interrupts with callbacks on core

    std::shared_ptr<displayManager> manager(new displayManager());
    std::shared_ptr<mainController> controller(new mainController(buttonPin, manager));
    manager->setController(controller);
    controller->addButton(18);
    manager->changeView();
    controller->buttonPressed(18);
    controller->mainLoop();

    manager.reset();
    controller.reset();

    bool led = false;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    pulseCounter counter{15, geigerPin};
    counter.startCounting();
    counter.pauseCounting();
    counter.startCounting();

    while (true) {
        sleep_ms(1000);
        gpio_put(PICO_DEFAULT_LED_PIN, led);
        led = !led;
        printf("total: %u\n", counter.getTotalCount());
        // controller->mainLoop();
    }
}