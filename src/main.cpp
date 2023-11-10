#include <stdio.h>
#include "pico/stdlib.h"
#define buttonPin 17
#define geigerPin 16
bool button = false;
bool geiger = false;
bool led = false;
unsigned eventmask = 0b100;
int main()
{
    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true); // enable interrupts with callbacks on core

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    gpio_init(geigerPin);
    gpio_set_dir(geigerPin, GPIO_IN);
    gpio_pull_down(geigerPin);
    gpio_set_irq_enabled(geigerPin, eventmask, true);
    gpio_add_raw_irq_handler(geigerPin, []()
                             {
            if(gpio_get_irq_event_mask(geigerPin)&eventmask) {
            gpio_acknowledge_irq(geigerPin, eventmask);
            geiger=true;
               } });

    gpio_init(buttonPin);
    gpio_set_dir(buttonPin, GPIO_IN);
    gpio_pull_down(buttonPin);
    gpio_set_irq_enabled(buttonPin, eventmask, true);
    gpio_add_raw_irq_handler(buttonPin, []()
                             {
            if(gpio_get_irq_event_mask(buttonPin)&eventmask) {
            gpio_acknowledge_irq(buttonPin, eventmask);
            button=true; } });

    while (true)
    {
        if (button)
        {
            printf("button\n");
            button = false;
        }
        if (geiger)
        {
            printf("geiger\n");
            geiger = false;
        }
        sleep_ms(300);
        gpio_put(PICO_DEFAULT_LED_PIN, led);
        led = !led;
        printf("loop\n");
    }
}