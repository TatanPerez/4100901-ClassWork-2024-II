#include <stdint.h>
#include "systick.h"
#include "gpio.h"

int main(void)
{
    configure_systick_and_start();
    configure_gpio();

    while (1) {
        handle_states();
    }
}

