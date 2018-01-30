/**
 * @file mcal_irq.cpp
 * @brief Interrupt Controller Initalization and management.
 * @description Initializes the attiny85 interrupt controller
 * and provides functions to enable and disable the interrupts.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */



#include <mcal_irq.h>

void mcal::irq::init(const config_type*)
{
  mcal::irq::enable_all();
}
