/**
 * @file mcal_usart.cpp
 * @brief USART module for ATMega328p abstraction layer.
 * @description Provides functions to initialize and 
 * control the usart module of the ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

//four modes of clock operation: Normal asynchronous, Double Speed asynchronous, Master synchronous and Slave synchronous mode

#include "mcal_usart.h"
#include <mcal_reg_access.h>
#include <avr/interrupt.h>

mcal::usart::usart_communication mcal::usart::the_usart;

void mcal::usart::init(const config_type*)
{
  
  //constexpr std::uint8_t reload_value_high = mcal::usart::baud_reload_value >>8;
  //  constexpr std::uint8_t reload_value_low = mcal::usart::baud_reload_value &0x00FF;
  // Change to templates parameters
  constexpr std::uint8_t reload_value_high = 0U;
  constexpr std::uint8_t reload_value_low = 51U;

  // Set baud rate 
  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::ubrr0h,
                      reload_value_high>::reg_set();

  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::ubrr0l,
                      reload_value_low>::reg_set();
  
  // Enable IRQs and receiver and transmitter 
  constexpr std::uint8_t tx_rx_enable_mask =  mcal::reg::bval7
    | mcal::reg::bval6
    | mcal::reg::bval5
    | mcal::reg::bval4 
    | mcal::reg::bval3;

  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::ucsr0b,
                      tx_rx_enable_mask>::reg_set();

  //This is default value: 9600 8N1
  // Set frame format: 8data, 1stop bit, No Parity
  constexpr std::uint8_t frame_format_mask =  mcal::reg::bval1
    | mcal::reg::bval2;
  //     | mcal::reg::bval3;

  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::ucsr0c,
                      frame_format_mask>::reg_set();
}

mcal::usart::size_type mcal::usart::usart_communication::recv_ready() const
{

  const mcal::usart::size_type count = recv_buffer.size();

  return count;
}

bool mcal::usart::usart_communication::recv(std::uint8_t& byte_to_recv)
{

  byte_to_recv = recv_buffer.out();

  return true;
}

template<typename recv_iterator_type>
bool mcal::usart::usart_communication::recv_n(recv_iterator_type first,
					      size_type count)
{
  const size_type count_to_recv = (std::min)(count, recv_ready());

  recv_iterator_type last = first + count_to_recv;

  bool recv_result = true;

  while(first != last)
    {
      std::uint8_t byte_to_recv;

      recv_result &= recv(byte_to_recv);

      typedef typename
	std::iterator_traits<recv_iterator_type>::value_type
	recv_value_type;

      *first = recv_value_type(byte_to_recv);

      ++first;
    }

  return recv_result;
}

template<typename recv_iterator_type>
bool recv_n(recv_iterator_type first, recv_iterator_type last)
{
  const mcal::usart::size_type count_to_recv = mcal::usart::size_type(std::distance(first, last));

  return recv_n(first, count_to_recv);
}

bool mcal::usart::usart_communication::send(const std::uint8_t byte_to_send)
{
  
  /* Wait for empty transmit buffer */
  if ( send_is_active == false )
    {
      //disable_rx_tx_interrupt();
      send_is_active = true;

      mcal::reg::dynamic_access<std::uint8_t, 
				std::uint8_t>::reg_set(
						       mcal::reg::udr0, 
						       byte_to_send
						       );
      //    enable_rx_tx_interrupt();
      return true;
    }
  else
    {
      send_buffer.in(byte_to_send);
      return false;
    }
}

//RX Complete
// Acumulamos en rx_buffer.
void __vector_18(void)
{

  const std::uint8_t byte_to_recv = mcal::reg::access<std::uint8_t, 
                                                        std::uint8_t, 
                                                        mcal::reg::udr0>::reg_get();

  mcal::usart::the_usart.recv_buffer.in(byte_to_recv);

}

//TX Data Register Empty
void __vector_19(void)
{
  
  if ( mcal::usart::the_usart.send_buffer.empty() )
    {
      mcal::usart::the_usart.send_is_active = false;
    }
  else
    {
const std::uint8_t byte_to_send = mcal::usart::the_usart.send_buffer.out();
      mcal::reg::dynamic_access<std::uint8_t, std::uint8_t>::reg_set(
								     mcal::reg::udr0,
								     byte_to_send);
    }
}

//TX Complete
void __vector_20(void)
{

}

 
