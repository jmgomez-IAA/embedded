/**
 * @file mcal_port.h
 * @brief Control a port on atmega328p.
 * @description Abstraction layer to control a port.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_PORT_EMBEDDED_2018_
#define _MCAL_PORT_EMBEDDED_2018_

//#include <mcal/mcal_port_base.h>
#include <mcal_reg_access.h>
#include <cstdint>

namespace mcal
{
  namespace port
  {
    typedef void config_type;

    inline void init(const config_type*) { }

    template<typename addr_type,
	     typename reg_type,
	     const addr_type port,
	     const reg_type bpos>
    class port_pin //: public port_base
    {
    public:
      static void set_direction_output()
      {
	// Set the port pin's direction to output.
	mcal::reg::access<addr_type, reg_type, pdir, bpos>::bit_set();
      }

      static void set_direction_input()
      {
	// Set the port pin's direction to input.
	mcal::reg::access<addr_type, reg_type, pdir, bpos>::bit_clr();
      }

      static void set_pin_high()
      {
	// Set the port output value to high.
	mcal::reg::access<addr_type, reg_type, port, bpos>::bit_set();
      }

      static void set_pin_low()
      {
	// Set the port output value to low.
	mcal::reg::access<addr_type, reg_type, port, bpos>::bit_clr();
      }

      static bool read_input_value()
      {
	// Read the port input value.
	return mcal::reg::access<addr_type, reg_type, pinp, bpos>::bit_get();
      }

      static void toggle_pin()
      {
	// Toggle the port output value.
	mcal::reg::access<addr_type, reg_type, port, bpos>::bit_not();
      }

    private:
      static constexpr addr_type pdir = port - 1U;
      static constexpr addr_type pinp = port - 2U;
    };
 
    extern const port_pin<std::uint8_t,
			  std::uint8_t,
			  mcal::reg::portb,
			  0x02U> portb2;

    extern const port_pin<std::uint8_t,
			  std::uint8_t,
			  mcal::reg::portb,
			  0x01U> portb1;
    extern const mcalport_pin<std::uint8_t,
			 std::uint8_t,
			 mcal::reg::portb,
			 0x07U> portD7;

    extern const port_pin<std::uint8_t,
			 std::uint8_t,
			 mcal::reg::portd,
			 0x06U> portD6;

  }
}

#endif // _MCAL_PORT_EMBEDDED_2018_
