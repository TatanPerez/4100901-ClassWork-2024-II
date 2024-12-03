#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
    volatile uint32_t BRR;
} GPIO_t;

#define GPIOA ((GPIO_t *)0x48000000) // Base address of GPIOA
#define GPIOC ((GPIO_t *)0x48000800) // Base address of GPIOC

#define LED_PIN 5 // Pin 5 of GPIOA
#define BUTTON_PIN 13 // Pin 13 of GPIOC

#define BUTTON_IS_PRESSED()    (!(GPIOC->IDR & (1 << BUTTON_PIN)))
#define BUTTON_IS_RELEASED()   (GPIOC->IDR & (1 << BUTTON_PIN))
#define TOGGLE_LED()           (GPIOA->ODR ^= (1 << LED_PIN))

void init_gpio_pin(GPIO_t *GPIOx, uint8_t pin, uint8_t mode);
void configure_gpio(void);
void EXTI15_10_IRQHandler(void);

uint16_t button_Getpressed(void);
void Clear_button_pressed(void);
uint16_t button_pressed_flag(void);
