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

namespace mcal
{
  namespace spi
  {
    typedef void config_type;
    typedef std::uint32_t value_type;

    void init(const config_type*);

    class spi_communication
    {
    public:
      //typedef circular_buffer<std::uint8_t, 16U> data_type;
      spi_communication();
      ~spi_communication();
      // The virtual communication interface.
      bool send(const std::uint8_t byte_to_send);
      //bool send(const data_type& data_to_send);
      bool recv(std::uint8_t& byte_to_recv);
      //bool recv(data_type& data_to_recv);
      std::size_t recv_ready() const;
      bool idle() const;
      // Specific channel select for SPI(TM).
      bool select_channel(const std::uint8_t ch);

    private:
      // Private class details.
      volatile bool send_is_active;
      std::uint8_t channel;
      // Friend interrupt service routine for Rx/Tx.
      friend void : : __vector_spi_rx_tx_isr();
    };    
  }
}

#endif // _MCAL_SPI_EMBEDDED_H_
