/**
 * @file mcal_led.h
 * @brief Control a led on portB4.
 * @description Abstraction layer to control a led on portb4.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_LED_EMBEDDED_2018_
#define _MCAL_LED_EMBEDDED_2018_

#include <cstdint>

class led
{
 public:
  typedef std::uint8_t port_type;
  typedef std::uint8_t bval_type;

  //Constructor
  led (const port_type p, const bval_type b) : port(p), bval(b)
  {
    //Set the portb output to low.
    *reinterpret_cast<volatile port_type*>(port) &= static_cast<bval_type>(~bval);
    
    //Set port direction to output (ddr is at addr port -1)
    *reinterpret_cast<volatile port_type*>(port -1) |= static_cast<bval_type>(bval);
    	   
  }
  
  void toggle(void) const
  {
    *reinterpret_cast<volatile port_type*>(port) ^= bval;
  }

 private:
  /*A led is located on a port with a value*/
  const port_type port;
  const bval_type bval;    
};

extern const led led_b1;



#endif //_MCAL_LED_EMBEDDED_2018_
