
/**
 * @file mcal_spi.h
 * @brief Control the SPI hardware module of ATMega328p.
 * @description Abstraction layer to control the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <mcal_cpu.h>
#include <mcal_spi.h>
//#include <mcal_port.h>
//#include <mcal/mcal_port_base.h>
#include <mcal_irq.h>
#include <mcal_reg_access.h>
#include <avr/interrupt.h>


mcal::spi::spi_communication mcal::spi::the_spi;

//const mcal::port::port_base cs_pin* = & mcal::port::portb2;


namespace 
{
  void enable_rx_tx_interrupt()
  {
    // Enable the spi end-of-transmission interrupt
    // by setting the spie bit in the spcr register.
    mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::spcr,
                      7U>::bit_set();
  }

  void disable_rx_tx_interrupt()
  {
    // Disable the spi end-of-transmission interrupt
    // by clearing the spie bit in the spcr register.
    mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::spcr,
                      7U>::bit_clr();
  }
}

/**
 * @brief Configure the SPI module of ATMega328p
 * @description Initializes the SPI module of the ATMega328p,
 * the default channel is SPI0, and configures it to Master Mode, 
 * Byte Order MSbit first and CLKDiv = fosc/64. 
 * Pin description:
 * PB[2] S\S\   // No more masters on bus are expected!!
 * PB[3] MOSI0
 * PB[4] MISO
 * PB[5] SCK0
 * 
 */
mcal::spi::spi_communication::spi_communication() : send_is_active(false), 
						    channel(0U)
{
  //Mask for port pins direction
  // Output for SS, MOSI, SCK.
  // Input for MISO.
  constexpr std::uint8_t pdir_mask = mcal::reg::bval2
      | mcal::reg::bval3
      | mcal::reg::bval5;


  // OPTIMIZATION
  // We should set port directions. If we change the port
  // we should change this static initialization.
  // Using a polimorphic class for port_base should make this code portable.
  // mcal::port::portb2.set_direction_output();
  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::ddrb,
                      pdir_mask>::reg_or();

  //  cs_pin->toggle_pin();
  //SS should be set to one.
  //Enable pull-up on MISO.
  constexpr std::uint8_t defout_mask = mcal::reg::bval2
      | mcal::reg::bval4;

  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::portb,
                      defout_mask>::reg_or();
  
  // Enable spi as master mode, clock idle to high, etc.
  // Set the spi clock to f_osc/64 = (1/4)MHz.
  constexpr std::uint8_t spcr_mask =   mcal::reg::bval1
    | mcal::reg::bval2
    | mcal::reg::bval3
    | mcal::reg::bval4
    | mcal::reg::bval6;

  //Set the SPI configuration.
  mcal::reg::access<std::uint8_t,
                    std::uint8_t,
                    mcal::reg::spcr,
                    spcr_mask>::reg_set();
}

mcal::spi::spi_communication::~spi_communication()
{
};

/*
* Might be conflictive if ISR at the same of read size.
*/

mcal::spi::spi_communication::size_type mcal::spi::spi_communication::recv_ready() const
{
  disable_rx_tx_interrupt();

  // Get the count of bytes in the receive buffer.
  const size_type count = recv_buffer.size();

  enable_rx_tx_interrupt();

  return count;
}

bool mcal::spi::spi_communication::recv(std::uint8_t& byte_to_recv)
{
  disable_rx_tx_interrupt();

  byte_to_recv = recv_buffer.out();

  enable_rx_tx_interrupt();

  return true;
}

bool mcal::spi::spi_communication::send(const std::uint8_t byte_to_send)
{

  if ( send_is_active == false){
    disable_rx_tx_interrupt();
    send_is_active = true;

    //Its better to do it out, to allow multiple slave.
    //  mcal::port::portb2.set_pin_low();

    mcal::reg::dynamic_access<std::uint8_t, std::uint8_t>::reg_set(mcal::reg::spdr, byte_to_send);

    enable_rx_tx_interrupt();
    //Might not be necessary.
    //mcal::irq::enable_all()
  }
  else
  {
    send_buffer.in(byte_to_send);
    //Might not be necessary.
    //mcal::irq::enable_all()
  }

  return send_is_active;
}


bool mcal::spi::spi_communication::idle() const
{
  disable_rx_tx_interrupt();
  const bool is_active = send_is_active;
  enable_rx_tx_interrupt();

  return (is_active == false); 
}


bool mcal::spi::spi_communication::busy() const
{
  return send_is_active;
}

//bool select_channel(const std::uint8_t ch);

	
//ISR(SPI_STC_vect)
void __vector_17()
{
  //Something received?
  const std::uint8_t byte_to_recv = mcal::reg::access<std::uint8_t, 
                                                        std::uint8_t, 
                                                        mcal::reg::spdr>::reg_get();
  mcal::spi::the_spi.recv_buffer.in(byte_to_recv);

  if( mcal::spi::the_spi.send_buffer.empty() )
  {
    disable_rx_tx_interrupt();
    mcal::spi::the_spi.send_is_active = false;

    //SS should be set to one.
    //    mcal::port::portb2.set_pin_high();
  }
  else
  {
    const uint8_t byte_to_send = mcal::spi::the_spi.send_buffer.out();
    mcal::reg::dynamic_access<std::uint8_t, std::uint8_t>::reg_set(mcal::reg::spdr, byte_to_send);
  }

}
