#include <pico/stdlib.h>

const uint8_t ROW_PINS[] = {
        6, 7, 8, 9
};

const uint8_t COL_PINS[] = {
        10, 11, 12
};

const char KEYPAD[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
};

void assignCol(uint8_t pin) {
    gpio_init(pin);

    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 1);
}

void assignRow(uint8_t pin) {
    gpio_init(pin);

    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_down(pin);
}

void initializeKeypad() {
    for (int i = 0; i <= sizeof(ROW_PINS) / sizeof(ROW_PINS[0]) - 1; i++) {
        assignRow(ROW_PINS[i]);
    }

    for (int i = 0; i <= sizeof(COL_PINS) / sizeof(COL_PINS[0]) - 1; i++) {
        assignCol(COL_PINS[i]);
    }
}

char requestValueFromKeypad() {
    int selectedRow = -1;
    int selectedCol = -1;

    while (true) {
        sleep_ms(10);

        // Attempt to find a pressed row
        for (int i = 0; i <= sizeof(ROW_PINS) / sizeof(ROW_PINS[0]) - 1; i++) {
            int value = gpio_get(ROW_PINS[i]);

            if (value == 1) {
                selectedRow = i;

                break;
            }
        }

        // If no row has been found
        if (selectedRow == -1) {
            continue;
        }

        // Check for pressed column
        for (int i = 0; i <= sizeof(COL_PINS) / sizeof(COL_PINS[0]) - 1; i++) {
            // Temporarily set col output to 0 to test if that's the one being selected
            gpio_put(COL_PINS[i], 0);

            int value = gpio_get(ROW_PINS[selectedRow]);

            // Set output back to 1
            gpio_put(COL_PINS[i], 1);

            if (value == 0) {
                selectedCol = i;

                break;
            }
        }

        // If no col has been found
        if (selectedCol == -1) {
            continue;
        }

        // Wait for button release loop
        while (true) {
            sleep_ms(10);

            // Get button power value
            int value = gpio_get(ROW_PINS[selectedRow]);

            // Check if button is still pressed
            if (value == 0) {
                return KEYPAD[selectedRow][selectedCol];
            }
        }
    }
}
