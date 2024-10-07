#include "../lib/STM32L432KC.h"
#include <stm32l432xx.h>
#include <stdio.h>

#define ASIGNAL_PIN PA5
#define BSIGNAL_PIN PA6
#define DELAY_TIM TIM2
#define COUNT_TIM TIM6

int delta = 0;
int off = 1;

int main(void) {
    // Enable pins as inputs
    gpioEnable(GPIO_PORT_A);
    pinMode(ASIGNAL_PIN, GPIO_INPUT);
    GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD5, 0b01); // Set PA5 as pull-up

    pinMode(BSIGNAL_PIN, GPIO_INPUT);
    GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD6, 0b01); // Set PA6 as pull-up

    // Initialize timers
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    initDelayTIM(DELAY_TIM);

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
    initTIM(COUNT_TIM);
    

    // TODO
    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    // 2. Configure EXTICR for the input button interrupt
    SYSCFG->EXTICR[1] |= _VAL2FLD(SYSCFG_EXTICR2_EXTI5, 0b000); // Select PA0
    SYSCFG->EXTICR[1] |= _VAL2FLD(SYSCFG_EXTICR2_EXTI6, 0b000); // Select PA1

    // Enable interrupts globally
    __enable_irq();

    // TODO: Configure interrupt for falling edge of GPIO pin for button
    // 1. Configure mask bit
    EXTI->IMR1 |= (1 << gpioPinOffset(ASIGNAL_PIN)); // Configure the mask bit
    EXTI->IMR1 |= (1 << gpioPinOffset(BSIGNAL_PIN)); // Configure the mask bit
    // 2. Disable rising edge trigger
    EXTI->RTSR1 |= (1 << gpioPinOffset(ASIGNAL_PIN));// Disable rising edge trigger
    EXTI->RTSR1 |= (1 << gpioPinOffset(BSIGNAL_PIN));// Disable rising edge trigger
    // 3. Enable falling edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(ASIGNAL_PIN));// Enable falling edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(BSIGNAL_PIN));// Enable falling edge trigger
    // 4. Turn on EXTI interrupt in NVIC_ISER.+-d
    NVIC->ISER[0] |= (1 << EXTI9_5_IRQn);
    //NVIC->ISER[0] |= (1 << EXTI9_5_IRQn);
    
    double rpm1 = 0;
    double rpm2 = 0;
    double rpm3 = 0;
    double rpm4 = 0;
    double rpm = 0;
    while(1){   
        delay_millis(DELAY_TIM, 250);
        if(COUNT_TIM->CNT > 45000){
          off = 1;
        }
        
        if(off){
          rpm = 0;
        }else {
          if(rpm == 0){
            rpm1 = 1/(double)(120*delta*4/1000000.0);
            rpm2 = rpm1;
            rpm3 = rpm1;
            rpm4 = rpm1;
          } else {
            rpm1 = rpm2;
            rpm2 = rpm3;
            rpm3 = rpm4;
            rpm4 = 1/(double)(120*delta*4/1000000.0);
          }
          rpm = (rpm1+rpm2+rpm3+rpm4)/4;
        }
        printf("RPM: %f\n", rpm);
        
    }

}

// TODO: What is the right name for the IRQHandler?
void EXTI9_5_IRQHandler(void){
    
    if (EXTI->PR1 & (1 << 6)){
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 |= (1 << 6);
        off = 0;
        if(((digitalRead(BSIGNAL_PIN) == 1) && (digitalRead(ASIGNAL_PIN) == 1)) || ((digitalRead(BSIGNAL_PIN) == 0) && (digitalRead(ASIGNAL_PIN) == 0))){
          delta = -COUNT_TIM->CNT;
        }
        COUNT_TIM->CNT = 0;
    }

     if (EXTI->PR1 & (1 << 5)){//EXTI->PR1 & (1 << 5)){
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 |= (1 << 5);
        off = 0;
        if(((digitalRead(BSIGNAL_PIN) == 1) && (digitalRead(ASIGNAL_PIN) == 1)) || ((digitalRead(BSIGNAL_PIN) == 0) && (digitalRead(ASIGNAL_PIN) == 0))){
          delta = COUNT_TIM->CNT;
        }
        COUNT_TIM->CNT = 0;
    }
}