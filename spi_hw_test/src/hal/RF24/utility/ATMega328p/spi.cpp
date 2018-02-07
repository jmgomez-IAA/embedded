/**
 * @file spi.cpp
 * @brief Bridge between SPI from RF24 and our SPI implementation.
 * @description Provides functions to initialize and 
 * control the spi module of the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */


#include "spi.h"

//SPI();
//  void begin(int busNo);
	
//  uint8_t transfer(uint8_t tx_);
//void transfernb(char* tbuf, char* rbuf, uint32_t len);
//  void transfern(char* buf, uint32_t len);

std::uint8_t transfer(std::uint8_t tx_)
{
  do 
  {
    std::bool spi_is_ready =  mcal::spi::the_spi.idle();
  }
  while( !spi_is_ready );

  mcal::spi::the_spi.send(tx_);

  std::bool spi_rx_ready = mcal::spi::the_spi.recv_ready();
  while(!spi_rx_ready)
  {
    spi_rx_ready = mcal::spi::the_spi.recv_ready();
  }

  const std::uint8_t byte_to_recv mcal::spi::the_spi_recv();
  return byte_to_recv;

}

