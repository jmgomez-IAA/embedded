/**
 * @file spi_hw_test.cpp
 * @brief Initiates a SPI communication.
 * @description Comunicates with a slave using SPI.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _SPI_HW_TEST_EMBEDDED_2018_
#define _SPI_HW_TEST_EMBEDDED_2018_

#include <mcal/mcal.h>
//#include <mcal_port.h>
#include <util/utility/util_time.h>
#include <util/utility/util_mmap_device.h>

namespace
{
  // Define a convenient local 32-bit timer type.
  typedef util::timer<std::uint32_t> timer_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t,
					mcal::reg::portb,
					0x00U> port_pin_t0;
}


int main()
{
  // Initialize the mcal.
  mcal::init();

  // Toggle led1 forever.
  //  led_b1.toggle();
  mcal::port::portb2.set_direction_output();
  mcal::port::portb1.set_direction_output();
  port_pin_t0::set_direction_output();
  for(;;)
  {
    //    mcal::port::portb1.toggle_pin();
    port_pin_t0::toggle_pin();
    //    if (! mcal::spi::the_spi.busy())    
    mcal::port::portb1.set_pin_low();
    mcal::port::portb2.set_pin_high();
    util::mmap_driver<0x12U, 0x25U>::writeRegister();
    mcal::port::portb1.set_pin_high();
    mcal::port::portb2.set_pin_low();
    //    mcal::spi::the_spi.send(0xFF);
    //    mcal::spi::the_spi.send(0xE0);
    //mcal::spi::the_spi.send(0x00);
    // Wait 1 second in a blocking delay.
    timer_type::blocking_delay(timer_type::seconds(1U));
  }
}

#endif //_SPI_HW_TEST_EMBEDDED_2018_
