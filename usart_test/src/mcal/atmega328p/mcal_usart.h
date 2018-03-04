/**
 * @file mcal_usart.h
 * @brief USART module for ATMega328p abstraction layer.
 * @description Provides functions to initialize and 
 * control the usart module of the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_USART_EMBEDDED_H_
#define _MCAL_USART_EMBEDDED_H_

#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <util/utility/util_circular_buffer.h>

extern "C" void __vector_18(void) __attribute__((signal, used, externally_visible));
extern "C" void __vector_19(void) __attribute__((signal, used, externally_visible));
extern "C" void __vector_20(void) __attribute__((signal, used, externally_visible));


namespace mcal
{
  namespace usart
  {

    // Enumeration of communication modes supported by USART 
    enum class UsartModeEL {
      ASYNC_NORMAL = 0,
	ASYNC_DOUBLE_SPEED = 1,
	SYNC_MASTER = 2
	};

    // Enumeration defining communication parity modes
    enum class UsartParityEL {
      NONE = 0,
	EVEN = 2,
	ODD = 3
	};

    // Enumeration defining communication stop bits
    enum class UsartStopBitEL {
      ONE = 1,
	TWO = 2
	};


    // Enumeration defining communication frame length
    enum class UsartFrameLengthEL {
      FIVE_BITS = 5,
	SIX_BITS = 6,
	SEVEN_BITS = 7,
	EIGHT_BITS = 8,
	NINE_BITS = 9
	};

    typedef void config_type;
    typedef std::uint32_t value_type;
    typedef std::uint8_t* data_type;
    typedef std::size_t size_type;

    void init(const config_type*);
    //    constexpr std::uint32_t F_CPU = 8000000UL; //0x7A1200UL; //
    constexpr std::uint32_t fosc = F_CPU; //0x1C2000U; // Clock Speed  1843200
    constexpr std::uint16_t baudrate = 9600;
    constexpr std::uint16_t baud_reload_value =  (fosc/(16*baudrate))-1;

    class usart_communication
    {
    public:
      typedef util::circular_buffer<std::uint8_t, 16U> buffer_type;
      //typedef util::circular_buffer<std::uint8_t, 16U> data_type;

      usart_communication() : send_is_active(false){};
      ~usart_communication() {};

      // The virtual communication interface.
      bool send(const std::uint8_t byte_to_send);
      //      bool send(const data_type& data_to_send);
      
      template<typename send_iterator_type>
      bool send_n(send_iterator_type first, send_iterator_type last)
      {
	bool send_result = true;

	while(first != last)
	  {
	    typedef typename
	      std::iterator_traits<send_iterator_type>::value_type
	      send_value_type;

	    const send_value_type value(*first);

	    send_result &= send(std::uint8_t(value));

	    ++first;
	  }

	return send_result;
      }


      size_type recv_ready() const;

      bool recv(std::uint8_t& byte_to_recv);
      //      bool recv(data_type& data_to_recv);

      //Blocking receive may be usefull
      template<typename recv_iterator_type>
      bool recv_n(recv_iterator_type first, size_type count);

      template<typename recv_iterator_type>
      bool recv_n(recv_iterator_type first, recv_iterator_type last);

      
      friend void ::__vector_18(void); 
      friend void ::__vector_19(void); 
      friend void ::__vector_20(void); 
    private:
      // Private class details.
      buffer_type send_buffer;
      buffer_type recv_buffer;

      volatile bool send_is_active;
      std::uint8_t channel;      

    };

    extern usart_communication the_usart;
  }
}

#endif //_MCAL_USART_EMBEDDED_H_
