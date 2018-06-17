
/**
 * @file mcal_led.cpp
 * @brief Control a led on portB4.
 * @description Abstraction layer to control a led on portb4.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */


#include <mcal_led.h>
#include <mcal_reg.h>
//#include <mcal_reg_access.h>

const led led_b1(mcal::reg::portb, mcal::reg::bval1);
