// TIM16.h
// Header for basic timer

#ifndef TIM16_H
#define TIM16_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM16_BASE (0x40014400) // base address of TIM16

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t TIM_CR1;     //< tim control register 1
  __IO uint32_t TIM_CR2;     // tim control register 2
  uint32_t      RESERVED0;    // Reserved,  
  __IO uint32_t TIM_DIER;   // tim DMA/Interrupt enable register
  __IO uint32_t TIM_SR;     // time status register
  __IO uint32_t TIM_EGR;    // tim event generation register
  __IO uint32_t TIM_CCMR1;    // tim capture/compare mode register
  uint32_t      RESERVED1;    // Reserved,  
  __IO uint32_t TIM_CCER;     // capture/compare mode register
  __IO uint32_t TIM_CNT;     // tim counter
  __IO uint32_t TIM_PSC;    // tim prescaler
  __IO uint32_t TIM_ARR;    // time auto reload register
  __IO uint32_t TIM_RCR;    // repetition counter register
  __IO uint32_t TIM_CCR1;    // capture/compare register 1
  uint32_t      RESERVED2;    // Reserved,
  uint32_t      RESERVED3;    // Reserved,
  uint32_t      RESERVED4;    // Reserved,
  __IO uint32_t TIM_BDTR;    // tim  break and dead-time register 
  __IO uint32_t TIM_DCR;    // DMA control register
  __IO uint32_t TIM_DMAR;    // 6 DMA address for full transfer
  __IO uint32_t TIM_OR1;    //  option register 1
  uint32_t      RESERVED5;    // Reserved,
  uint32_t      RESERVED6;    // Reserved,
  uint32_t      RESERVED7;    // Reserved,
  __IO uint32_t TIM_OR2;    //  option register 2


} TIM16_TypeDef;

#define TIM16 ((TIM16_TypeDef *) TIM16_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////
void setUpPWM(int frequency, int dutyCycle);

void changeFreq(int frequency, int dutyCycle);

#endif