// TIM16.c
// Source code for TIM16 functions
#include "../lib/TIM67.h"

void setUpTIM6() {
    TIM6->TIM_PSC = 0b1010; // scale clock down by 10
    TIM6->TIM_EGR |= (0b1 << 0); // enableUpdate generation
    TIM6->TIM_SR &= ~(0b1 << 0);
    TIM6->TIM_CR1 |= (0b1 << 0); // enable the counter of tim6
}
void delayTIM6(int ms) {
    TIM6->TIM_ARR = (ms*98.453);
    while (TIM6->TIM_SR == 0){
     
    }
    TIM6->TIM_SR &= ~(0b1 << 0);
}