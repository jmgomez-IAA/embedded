/**
 * @file mcal_port_base.h
 * @brief Interface class for the implementation of Ports
 * @description Abstraction layer to control a port.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_PORTBASE_EMBEDDED_2018_
#define _MCAL_PORTBASE_EMBEDDED_2018_


namespace mcal
{
  namespace port
  {
    class port_base
    {
    public:
      virtual void set_direction_output()= 0;
      virtual void set_direction_input()=0;
      virtual void set_pin_high() = 0;
      virtual void set_pin_low() = 0;
      virtual bool read_input_value() = 0;
      virtual void toggle_pin() = 0;

      virtual ~port_base();
    private:
      port_base(const port_base &) = delete;
      const port_base& operator=(const port_base&) = delete;
      
    };
  }
}

#endif //_MCAL_PORTBASE_EMBEDDED_2018_
