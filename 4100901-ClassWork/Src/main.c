#include <stdint.h>
#include "systick.h"
#include "gpio.h"
<<<<<<< HEAD
=======

>>>>>>> 23a42f6a6299a7236a8e71a8c320f2af2c881527

int main(void)
{
    configure_systick_and_start();
    configure_gpio();

    while (1) {
<<<<<<< HEAD
        handle_states();
=======
        switch (state) {
        case 0: // idle
            if (gpio_button_is_pressed() != 0) { // If button is pressed
                state = 1;
            } else if (systick_GetTick() >= 500) { // Blink LED every 500 ms
                state = 2;
            }
            break;
        case 1: // button pressed
            if (gpio_button_is_pressed() == 0) { // If button is released
                systick_reset(); // Reset counter
                state = 0;
            }
            break;
        case 2: // led toggle
            gpio_toggle_led();
            systick_reset(); // Reset counter
            state = 0;
            break;
        default:
            break;
        }
        
>>>>>>> 23a42f6a6299a7236a8e71a8c320f2af2c881527
    }
}

