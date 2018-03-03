
/**
 * @file mcal_port.cpp
 * @brief Declares the ports for the project.
 * @description Abstraction layer to control the ports of ATMega328p for the  SPI module.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */


#include <mcal_port.h>
#include <mcal_reg.h>

mcal::port::port_pin<std::uint8_t,
		     std::uint8_t,
		     mcal::reg::portb,
		     0x02U> portb2;

mcal::port::port_pin<std::uint8_t,
		     std::uint8_t,
		     mcal::reg::portb, 
		     0x01U> portb1;

mcal::port::port_pin<std::uint8_t,
		     std::uint8_t,
		     mcal::reg::portb,
		     0x07U> portD7;

mcal::port::port_pin<std::uint8_t,
		     std::uint8_t,
		     mcal::reg::portd,
		     0x06U> portD6;


