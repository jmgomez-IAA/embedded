
/**
 * @file mcal_spi.h
 * @brief Control the SPI hardware module of ATMega328p.
 * @description Abstraction layer to control the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <mcal_cpu.h>
#include <mcal_reg.h>
#include <mcal_spi.h>

/**
 * @brief Configure the SPI module of ATMega328
 * @description 
 */
mcal::spi::spi_communication::spi_communication() : send_is_active(false), 
						    channel(0U)
{
  //Mask for port pins direction
  constexpr std::uint8_t pdir_mask =   mcal::reg::bval2
    | mcal::reg::bval3
    | mcal::reg::bval5;

  // Enable spi as master mode, clock idle to high, etc.
  // Set the spi clock to f_osc/64 = (1/4)MHz.
  constexpr std::uint8_t spcr_mask =   mcal::reg::bval1
    | mcal::reg::bval2
    | mcal::reg::bval3
    | mcal::reg::bval4
    | mcal::reg::bval6;

  //Set the port direction for the chip select.
}

mcal::spi::spi_communication::~spi_communication()
{
}:

