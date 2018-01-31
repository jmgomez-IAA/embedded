
/**
 * @file mcal_spi.h
 * @brief Control the SPI hardware module of ATMega328p.
 * @description Abstraction layer to control the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <mcal_cpu.h>
#include <mcal_spi.h>
#include <mcal_irq.h>
#include <mcal_reg_access.h>
#include <avr/interrupt.h>


mcal::spi::spi_communication mcal::spi::the_spi;

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


  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::ddrb,
                      pdir_mask>::reg_or();

  //SS should be set to one.
  mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::portb,
                      pdir_mask>::reg_or();
  
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

bool mcal::spi::spi_communication::send(const std::uint8_t byte_to_send)
{

  //if ( send_is_active == false){
    disable_rx_tx_interrupt();
    send_is_active = true;

    //    bit_clr()
    mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::portb,
                      2U>::bit_clr();

    constexpr std::uint8_t test_spi_value = 0xA5;
    mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::spdr,
                      test_spi_value>::reg_set();    

    enable_rx_tx_interrupt();
    //}

  return send_is_active;
}

/*
bool mcal::spi::spi_communication::idle() const
{
  disable_rx_tx_interrupt();
  const bool is_active = send_is_active;
  enable_rx_tx_interrupt();

  return (is_active == false); 
}
*/
bool mcal::spi::spi_communication::busy() const
{
  return send_is_active;
}

//bool select_channel(const std::uint8_t ch);

	
//extern "C" void SPI_STC_vect(void)  __attribute__ ((signal));

//ISR(SPI_STC_vect)
ISR(SPI_STC_vect)
{
 
  //SS should be set to one.
  mcal::reg::access<std::uint8_t,
                    std::uint8_t,
                    mcal::reg::portb,
                    2U>::bit_set();

  disable_rx_tx_interrupt();

  //  mcal::spi::the_spi.send_is_active = false;
}
