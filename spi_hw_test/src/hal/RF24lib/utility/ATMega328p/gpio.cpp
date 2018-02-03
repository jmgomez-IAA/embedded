/**
 * @file mcal_port.h
 * @brief Control a port on atmega328p.
 * @description Abstraction layer to control a port.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include "gpio.h"


typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval2> pinDigital2;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval3> pinDigital3;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval4> pinDigital4;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval5> pinDigital5;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval6> pinDigital6;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval7> pinDigital7;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portb,
                             mcal::reg::bval0> pinDigital8;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval1> pinDigital9;

typedef mcal::port::port_pin<std::uint8_t, 
                             std::uint8_t,
                             mcal::reg::portd,
                             mcal::reg::bval2> pinDigital10;

static void write(int port,int value)
{
  switch ( port )
  {
    case 2:
      if (value)
        pinDigital2.set_pin_high();
      else
        pinDigital2.set_pin_low();           
      break;

    case 3:
      if (value)
        pinDigital3.set_pin_high();
      else
        pinDigital3.set_pin_low();           
      break;

    case 4:
      if (value)
        pinDigital4.set_pin_high();
      else
        pinDigital4.set_pin_low();           
      break;

    case 5:
      if (value)
        pinDigital5.set_pin_high();
      else
        pinDigital5.set_pin_low();           
      break;

    case 6:
      if (value)
        pinDigital6.set_pin_high();
      else
        pinDigital6.set_pin_low();           
      break;

    case 7:
      if (value)
        pinDigital7.set_pin_high();
      else
        pinDigital7.set_pin_low();
      break;

    case 8:
      if (value)
        pinDigital8.set_pin_high();
      else
        pinDigital8.set_pin_low();
      break;

    case 9:
      if (value)
        pinDigital9.set_pin_high();
      else
        pinDigital9.set_pin_high();
      break;

    case 10:
      if (value)
        pinDigital10.set_pin_high();
      else
        pinDigital10.set_pin_low();
      break;

    default:
      mcal::cpu::nop();
  }
}


static void GPIO::open(int port, int DDR)
{
  switch ( port )
  {
    case 2:
      if (DDR)
        pinDigital2.set_direction_output();
      else
        pinDigital2.set_direction_input();           
      break;

    case 3:
      if (DDR)
        pinDigital3.set_direction_output();
      else
        pinDigital3.set_direction_input();           
      break;

    case 4:
      if (DDR)
        pinDigital4.set_direction_output();
      else
        pinDigital4.set_direction_input();           
      break;

    case 5:
      if (DDR)
        pinDigital5.set_direction_output();
      else
        pinDigital5.set_direction_input();           
      break;

    case 6:
      if (DDR)
        pinDigital6.set_direction_output();
      else
        pinDigital6.set_direction_input();           
      break;

    case 7:
      if (DDR)
        pinDigital7.set_direction_output();
      else
        pinDigital7.set_direction_input();           
      break;

    case 8:
      if (DDR)
        pinDigital8.set_direction_output();
      else
        pinDigital8.set_direction_input();           
      break;

    case 9:
      if (DDR)
        pinDigital9.set_direction_output();
      else
        pinDigital9.set_direction_input();           
      break;

    case 10:
      if (DDR)
        pinDigital10.set_direction_output();
      else
        pinDigital10.set_direction_input();           
      break;

    default:
      mcal::cpu::nop();
  }

}
