#include "gpio.h"
#include "systick.h"

void handle_states(void)
{
    uint8_t state = 0; // state of the FSM
    switch (state) {
        case 0: // idle
            if (button_pressed_flag()) { // If button is pressed
                state = 1;
            } else if (systick_GetTick() >= 500) { // Blink LED every 500 ms
                state = 2;
            }
            break;
        case 1: // button pressed
            if (BUTTON_IS_RELEASED()) { // If button is released
                Clear_button_pressed(); // Clear button pressed flag
                systick_reset(); // Reset counter
                state = 0;
            }
            break;
        case 2: // led toggle
            TOGGLE_LED(); // Toggle LED
            systick_reset(); // Reset counter
            state = 0;
            break;
        default:
            break;
    }
}
