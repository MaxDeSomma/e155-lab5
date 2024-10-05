// TIM16.c
// Source code for TIM16 functions
#include "../lib/TIM16.h"

void setUpPWM(int frequency, int dutyCycle) {
    //TIM16->TIM_PSC |= (0b1 << 1); // set clock prescaler
    TIM16->TIM_CR1 |= (0b1 << 7); // enable auto preload reload
    TIM16->TIM_ARR &= 0;
    TIM16->TIM_ARR = (984533/frequency); // set the auto reload register


    TIM16->TIM_CCER |= (0b1 << 0); // enable capture compare 1
    TIM16->TIM_CCR1 = TIM16->TIM_ARR * (dutyCycle/100.0); // 50%  duty cycle
    TIM16->TIM_CCMR1 &= ~(0b11 << 0); // set CC1 as output
    TIM16->TIM_CCMR1 |= (0b1 << 6); // setting to pwm mode 1
    TIM16->TIM_CCMR1 |= (0b1 << 5); // setting to pwm mode 1
    
    TIM16->TIM_BDTR |= (0b1 << 15); // enable main output enable 
    
    TIM16->TIM_CCMR1 |= (0b1 << 3); // enable pre load register

   
    
    TIM16->TIM_EGR |= (0b1 << 0); // enableUpdate generation
    TIM16->TIM_CR1 |= (0b1 << 0); //enable the counter for timer 16
}

void changeFreq(int frequency, int dutyCycle) {
  TIM16->TIM_ARR = (984533/frequency);
  TIM16->TIM_CCR1 = TIM16->TIM_ARR * (dutyCycle/100.0);
  TIM16->TIM_EGR |= (0b1 << 0);
}
