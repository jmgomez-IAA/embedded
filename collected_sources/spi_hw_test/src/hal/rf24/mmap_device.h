/**
 * @file mmap_device.h
 * @brief Abstraction layer to access memory mapped register using SPI.
 * @description 
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _UTIL_MMAP_SPI_EMBEDDED_H_
  #define _UTIL_MMAP_SPI_EMBEDDED_H_

#include <cstdint>
#include <mcal_spi.h>
#include <mcal_port.h>


namespace util
{

  template <typename port_pin_type,
	    std::uint8_t address,
	    std::uint8_t value>
  class mmap_driver
  {
    static void writeRegister()
    {
      port_pin_type::set_pin_low();
      mcal::spi::the_spi.send(address);
      mcal::spi::the_spi.send(value);
      port_pin_type::set_pin_high();
    }

    static std::uint8_t readRegister()
    {
      std::uint8_t data_to_recv;
      port_pin_type::set_pin_low();
      mcal::spi::the_spi.send(address);
      mcal::spi::the_spi.send(value);
	
      if ( mcal::spi::the_spi.recv_ready() ){
	mcal::spi::the_spi.recv(data_to_recv);
	mcal::spi::the_spi.recv(data_to_recv);
      }
      port_pin_type::set_pin_high();
      return data_to_recv;
    }    
  };
}



#endif //_UTIL_MMAP_SPI_EMBEDDED_H_
