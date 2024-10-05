// TIM67.h
// Header for basic timer

#ifndef TIM67_H
#define TIM67_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM6_BASE (0x40001000UL) // base address of TIM6
#define TIM7_BASE (0x40001400UL) // base address of TIM7

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t TIM_CR1;     //< tim control register 1
  __IO uint32_t TIM_CR2;     // tim control register 2
  uint32_t      RESERVED;    // Reserved,  
  __IO uint32_t TIM_DIER;   // tim DMA/Interrupt enable register
  __IO uint32_t TIM_SR;     // time status register
  __IO uint32_t TIM_EGR;    // tim event generation register
  uint32_t      RESERVED1;    // Reserved,
  uint32_t      RESERVED2;    // Reserved,
  uint32_t      RESERVED3;    // Reserved,
  __IO uint32_t TIM_CNT;     // tim counter
  __IO uint32_t TIM_PSC;      // time prescaler
  __IO uint32_t TIM_ARR;     // time auto reload register                                                           

} TIM_TypeDef;

#define TIM6 ((TIM_TypeDef *) TIM6_BASE)
#define TIM7 ((TIM_TypeDef *) TIM7_BASE)

void setUpTIM6();
void delayTIM6(int ms);

#endif