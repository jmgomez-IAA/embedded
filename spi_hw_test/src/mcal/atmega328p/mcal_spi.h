/**
 * @file mcal_spi.h
 * @brief SPI module for ATMega328p abstraction layer.
 * @description Provides functions to initialize and 
 * control the spi module of the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_SPI_EMBEDDED_H_
  #define _MCAL_SPI_EMBEDDED_H_

#include <cstdint>
#include <cstddef>
#include <util/utility/util_circular_buffer.h>

//extern "C" void SPI_STC_vect(void) __attribute__((signal, used, externally_visible));
extern "C" void __vector_17(void) __attribute__((signal, used, externally_visible));

namespace mcal
{
  namespace spi
  {
    typedef void config_type;
    typedef std::uint32_t value_type;
    typedef std::uint8_t* data_type;
    inline void init(const config_type*){}

    class spi_communication
    {
    public:
      typedef util::circular_buffer<std::uint8_t, 16U> buffer_type;
      typedef std::size_t size_type;
      spi_communication();    
      ~spi_communication();

      // The virtual communication interface.
      bool send(const std::uint8_t byte_to_send);
      size_type recv_ready() const;
      //Blocking receive may be usefull
      bool recv(std::uint8_t& byte_to_recv);
      bool idle() const;

      //bool send(const data_type& data_to_send){ return true;}
      //bool recv(data_type& data_to_recv);

      // Specific channel select for SPI(TM).
      // bool select_channel(const std::uint8_t ch);
      bool busy() const;
      //bool receive_buffer_is_empty()

      //ISR for transmission end.      
      //friend void ::SPI_STC_vect(void);
      friend void ::__vector_17(void); 

    private:
      // Private class details.
      buffer_type send_buffer;
      buffer_type recv_buffer;

      volatile bool send_is_active;
      std::uint8_t channel;
    };

    extern spi_communication the_spi;
  }
}

#endif // _MCAL_SPI_EMBEDDED_H_
