/**
 * @file mcal_irq.h
 * @brief Interrupt Controller Initalization and management.
 * @description Initializes the attiny85 interrupt controller
 * and provides functions to enable and disable the interrupts.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_IRQ_EMBEDDED_2018_
#define _MCAL_IRQ_EMBEDDED_2018_

namespace mcal
{
  namespace irq
  {
    typedef void config_type;

    void init(const config_type *);

    inline void enable_all() { asm volatile ("sei"); }
    inline void disable_all() { asm volatile ("cli"); }
  }
}

#endif //_MCAL_IRQ_EMBEDDED_2018_

