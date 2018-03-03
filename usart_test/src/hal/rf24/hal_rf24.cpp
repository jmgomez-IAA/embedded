/**
 * @file mcal_spi.h
 * @brief SPI module for ATMega328p abstraction layer.
 * @description Provides functions to initialize and 
 * control the spi module of the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include "hal_rf24.h"


template <typename csn_pin,
	  typename ce_pin>
hal::rf24::RF24<csn_pin, ce_pin>::RF24() : p_variant(false),
					   payload_size(32), dynamic_payloads_enabled(false), 
					   addr_width(5),csDelay(5)
{

  csn_pin::set_direction_output();
  ce_pin::set_direction_output();

  pipe0_reading_address[0]=0;

}

template <typename csn_pin,
	  typename ce_pin>
hal::rf24::RF24<csn_pin, ce_pin>::RF24(std::uint8_t _cepin, std::uint8_t _cspin) : 
  ce_pin(_cepin), csn_pin(_cspin), p_variant(false),
  payload_size(32), dynamic_payloads_enabled(false), 
  addr_width(5),csDelay(5)//,pipe0_reading_address(0)
{
  csn_pin::set_direction_output();
  ce_pin::set_direction_output();

  pipe0_reading_address[0]=0;

}

//Begin the operation of the chip.
template <typename csn_pin,
	  typename ce_pin>
void hal::rf24::RF24<csn_pin, ce_pin>::begin(void)
{
  
  // Initialize pins. Maybe better on constructor!!! 
  //  port_pin_type::set_direction_output(); //(ce_pin,OUTPUT);
  // Must allow the radio time to settle else configuration bits will not necessarily stick.
  // This is actually only required following power up but some settling time also appears to
  // be required after resets too. For full coverage, we'll always assume the worst.
  // Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
  // Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
  // WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
  
  timer_type::blocking_delay(timer_type::milliseconds(5U)); //delay( 5 ) ;

  // Reset NRF_CONFIG and enable 16-bit CRC.
  //  write_register( NRF_CONFIG, 0x0C ) ;
  csn_pin::set_pin_low();
  util::mmap_driver<NRF_CONFIG,
		    0x0CU>::write_register();
  csn_pin::set_pin_high();

  // Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
  // WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
  // sizes must never be used. See documentation for a more complete explanation.
  constexpr conf::retries_timeout = (0x05U&0x0FU)<<ARD | (15U&0xf)<<ARC
  //  setRetries(5,15); SETUP_RETR,
  util::mmap_driver<SETUP_RETR,
		    retries_timeout>::write_register();
  // Reset value is MAX
  //setPALevel( RF24_PA_MAX ) ;//Comentado en el original.
  //  constexpr conf::pa_level = (le
  //  util::mmap_driver<RF_SETUP,0>::read_register();

  // check for connected module and if this is a p nRF24l01 variant
  //
  /*
  if( setDataRate( RF24_250KBPS ) )
  {
    p_variant = true ;
  }
  setup = read_register(RF_SETUP);
  */
  /*if( setup == 0b00001110 )     // register default for nRF24L01P
  {
    p_variant = true ;
  }*/
  
  // Then set the data rate to the slowest (and most reliable) speed supported by all
  // hardware.
  //  setDataRate( RF24_1MBPS ) ;

  // Initialize CRC and request 2-byte (16bit) CRC
  //setCRCLength( RF24_CRC_16 ) ;

  // Disable dynamic payloads, to match dynamic_payloads_enabled setting - Reset value is 0
  /*
  toggle_features();
  write_register(FEATURE,0 );
  write_register(DYNPD,0);
  dynamic_payloads_enabled = false;
  */
  // Reset current status
  // Notice reset and flush is the last thing we do
  //write_register(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Set up default configuration.  Callers can always change it later.
  // This channel should be universally safe and not bleed over into adjacent
  // spectrum.
  //setChannel(76);

  // Flush buffers
  //flush_rx();
  //flush_tx();

  //powerUp(); //Power up by default when begin() is called

  // Enable PTX, do not write CE high so radio will remain in standby I mode ( 130us max to transition to RX or TX instead of 1500us from powerUp )
  // PTX should use only 22uA of power
  //write_register(NRF_CONFIG, ( read_register(NRF_CONFIG) ) & ~_BV(PRIM_RX) );

  // if setup is 0 or ff then there was no response from module
  // return ( setup != 0 && setup != 0xff );
  return 0;
}

//Checks if the chip is connected to the SPI bus      
std::bool hal::rf24::RF24::isChipConnected()
{
  /*
  std::uint8_t setup = read_register(SETUP_AW);
  if(setup >= 1 && setup <= 3)
  {
    return true;
  }
  */
  return false;
}

//Start listening on the pipes opened for reading.
void hal::rf24::RF24::startListening(void)
{}

//Stop listening for incoming messages, and switch to transmit mode.
void hal::rf24::RF24::stopListening(void)
{}

//Check whether there are bytes available to be read
std::bool hal::rf24::RF24::available(void)
{}

//Read the available payload
void hal::rf24::RF24::read( void* buf, std::uint8_t len )
{}

//Wire a payload to the destination.
std::bool hal::rf24::RF24::write( const void* buf, std::uint8_t len )
{};

//Open a pipe for writing via byte array. Old addressing format retained for compatibility.
void hal::rf24::RF24::openWritingPipe(const std::uint8_t *address)
{};

//Open a pipe for reading
void hal::rf24::RF24::openReadingPipe(std::uint8_t number, const std::uint8_t *address)
{};

virtual hal::rf24::RF24::~RF24();
