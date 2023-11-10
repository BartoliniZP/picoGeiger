#include <stdio.h>

#include "pico/stdlib.h"
#include "pulseCounter.h"
#define buttonPin 17
#define geigerPin 16

int main() {
    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true);  // enable interrupts with callbacks on core

    bool led = false;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    pulseCounter counter{15, geigerPin};
    counter.startCounting();
    counter.pauseCounting();
    counter.startCounting();

    while (true) {
        sleep_ms(300);
        gpio_put(PICO_DEFAULT_LED_PIN, led);
        led = !led;
        printf("last period counts: %u\n", counter.getCountsInLastPeriod());
    }
}