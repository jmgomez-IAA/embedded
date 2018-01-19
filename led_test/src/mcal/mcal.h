/**
 * @file mcal.h
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_EMBEDDED_2018_
#define _MCAL_EMBEDDED_2018_

#include <mcal_irq.h>
#include <mcal_led.h>

namespace mcal
{
  void init();
}

#endif //_MCAL_EMBEDDED_2018_
