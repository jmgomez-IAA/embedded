/**
 * @file usart_hw_test.cpp
 * @brief Initiates a UART communication.
 * @description Comunicates with a UART.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _UART_HW_TEST_EMBEDDED_2018_
#define _UART_HW_TEST_EMBEDDED_2018_

#include <mcal/mcal.h>
#include <util/utility/util_time.h>
#include <array>

namespace
{
  // Define a convenient local 32-bit timer type.
  typedef util::timer<std::uint32_t> timer_type;
}

int main()
{
  // Initialize the mcal.
  mcal::init();

  constexpr std::array<std::uint8_t, 7U> my_array{
    { 'h', 'o', 'o', 'l', 'a', '\n', '\r' }
  };

  for(;;)
  {

    // Toggle led1 forever.
    led_b1.toggle();

    if (mcal::usart::the_usart.recv_ready() > 0)
      {
	std::uint8_t byte_to_send = 0;
	// Receive the data.
        mcal::usart::the_usart.recv(byte_to_send);
	// Transmit the test message
	mcal::usart::the_usart.send(byte_to_send);
      }
    else
      {
	//std::string msg ("Test message");
	mcal::usart::the_usart.send_n(my_array.begin(), my_array.end());
      }

    // Wait 1 second in a blocking delay.
    timer_type::blocking_delay(timer_type::seconds(1U));
  }
}

#endif //_UART_HW_TEST_EMBEDDED_2018_
