/**
 * @file mcal.cpp
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <mcal/mcal.h>

void mcal::init()
{
  mcal::irq::init(nullptr);
}
