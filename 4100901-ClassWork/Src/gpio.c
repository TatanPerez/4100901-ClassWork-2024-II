#include "gpio.h"
<<<<<<< HEAD
#include "systick.h"

typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t CFGR1;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CFGR2;
} SYSCFG_t;

typedef struct {
    volatile uint32_t IMR1;
    volatile uint32_t EMR1;
    volatile uint32_t RTSR1;
    volatile uint32_t FTSR1;
    volatile uint32_t SWIER1;
    volatile uint32_t PR1;
    volatile uint32_t IMR2;
    volatile uint32_t EMR2;
    volatile uint32_t RTSR2;
    volatile uint32_t FTSR2;
    volatile uint32_t SWIER2;
    volatile uint32_t PR2;
} EXTI_t;



#define RCC_BASE 0x40021000
#define RCC_AHB2ENR ((uint32_t *)(RCC_BASE + 0x4C))
#define RCC_APB2ENR ((uint32_t *)(RCC_BASE + 0x60))

#define SYSCFG_BASE 0x40010000
#define SYSCFG ((SYSCFG_t *)SYSCFG_BASE)


//
=======

>>>>>>> 23a42f6a6299a7236a8e71a8c320f2af2c881527
#define EXTI_BASE 0x40010400
#define EXTI ((EXTI_t *)EXTI_BASE)

#define EXTI15_10_IRQn 40
#define NVIC_ISER1 ((uint32_t *)(0xE000E104)) // NVIC Interrupt Set-Enable Register

<<<<<<< HEAD
volatile uint16_t button_pressed = 0; // Flag to indicate button press
=======

#define RCC_APB2ENR ((uint32_t *)(RCC_BASE + 0x60)) // APB2 peripheral clock enable register

#define SYSCFG_BASE 0x40010000
#define SYSCFG ((SYSCFG_t *)SYSCFG_BASE)

#define RCC_BASE 0x40021000
#define RCC_AHB2ENR ((uint32_t *)(RCC_BASE + 0x4C))

#define GPIOA ((GPIO_t *)0x48000000) // Base address of GPIOA
#define GPIOC ((GPIO_t *)0x48000800) // Base address of GPIOC

#define LED_PIN 5 // Pin 5 of GPIOA
#define BUTTON_PIN 13 // Pin 13 of GPIOC

#define BUTTON_IS_PRESSED()    (!(GPIOC->IDR & (1 << BUTTON_PIN)))
#define BUTTON_IS_RELEASED()   (GPIOC->IDR & (1 << BUTTON_PIN))
#define TOGGLE_LED()           (GPIOA->ODR ^= (1 << LED_PIN))

volatile uint8_t button_pressed = 0; // Flag to indicate button press
>>>>>>> 23a42f6a6299a7236a8e71a8c320f2af2c881527

void init_gpio_pin(GPIO_t *GPIOx, uint8_t pin, uint8_t mode)
{
    GPIOx->MODER &= ~(0x3 << (pin * 2)); // Clear MODER bits for this pin
    GPIOx->MODER |= (mode << (pin * 2)); // Set MODER bits for this pin
}

void configure_gpio(void)
{
    *RCC_AHB2ENR |= (1 << 0) | (1 << 2); // Enable clock for GPIOA and GPIOC

    // Enable clock for SYSCFG
    *RCC_APB2ENR |= (1 << 0); // RCC_APB2ENR_SYSCFGEN

    // Configure SYSCFG EXTICR to map EXTI13 to PC13
    SYSCFG->EXTICR[3] &= ~(0xF << 4); // Clear bits for EXTI13
    SYSCFG->EXTICR[3] |= (0x2 << 4);  // Map EXTI13 to Port C

    // Configure EXTI13 for falling edge trigger
    EXTI->FTSR1 |= (1 << BUTTON_PIN);  // Enable falling trigger
    EXTI->RTSR1 &= ~(1 << BUTTON_PIN); // Disable rising trigger

    // Unmask EXTI13
    EXTI->IMR1 |= (1 << BUTTON_PIN);

    init_gpio_pin(GPIOA, LED_PIN, 0x1); // Set LED pin as output
    init_gpio_pin(GPIOC, BUTTON_PIN, 0x0); // Set BUTTON pin as input

    // Enable EXTI15_10 interrupt
    *NVIC_ISER1 |= (1 << (EXTI15_10_IRQn - 32));
}

<<<<<<< HEAD
=======
uint8_t gpio_button_is_pressed(void)
{
    return BUTTON_IS_PRESSED();
}

void gpio_toggle_led(void)
{
    TOGGLE_LED();
}

>>>>>>> 23a42f6a6299a7236a8e71a8c320f2af2c881527
void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1 << BUTTON_PIN)) {
        EXTI->PR1 = (1 << BUTTON_PIN); // Clear pending bit
        button_pressed = 1; // Set button pressed flag
    }
}
<<<<<<< HEAD

uint16_t button_Getpressed(void) {
    return button_pressed;
}

uint16_t button_pressed_flag(void)    // Set button pressed flag
{
    return button_pressed != 0;
}

void Clear_button_pressed(void) // Clear button pressed flag
{
    button_pressed = 0;
}
=======
>>>>>>> 23a42f6a6299a7236a8e71a8c320f2af2c881527
