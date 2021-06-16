#include <pico/stdlib.h>
#include "keypad.h"


int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    initializeKeypad();

    while (true) {
        char value = requestValueFromKeypad();

        switch (value) {
            case '1':
                gpio_put(PICO_DEFAULT_LED_PIN, 1);
                break;
            case '4':
                gpio_put(PICO_DEFAULT_LED_PIN, 0);
                break;
        }
    }
}
