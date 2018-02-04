/**
 * @file mcal_spi.h
 * @brief SPI module for ATMega328p abstraction layer.
 * @description Provides functions to initialize and 
 * control the spi module of the SPI module of ATMega328p.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _HAL_RF24_EMBEDDED_H_
  #define _HAL_RF24_EMBEDDED_H_

#include <cstdint>
#include <mcal_spi.h>
#include <mcal_port.h>
#include <util/utility/util_time.h>
#include "mmap_device.h"

namespace hal
{
  namespace rf24
  {
    // Power Amplifier level for setPALevel().
    typedef enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } rf24_pa_dbm_e;
    // RF24 Wireless Data rate. 
    typedef enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } rf24_datarate_e;
    // CRC Length.  How big (if any) of a CRC is included.
    typedef enum { RF24_CRC_DISABLED = 0, RF24_CRC_8, RF24_CRC_16 } rf24_crclength_e;

    /**
     * Driver for nRF24L01(+) 2.4GHz Wireless Transceiver
     * Uses the SPI module to communicate.
     * Uses the Port Module to manage pins.
     */
    template <typename port_pin_type>
    class RF24
    {
    private:
      std::uint8_t ce_pin;
      std::uint8_t csn_pin;
      // False for RF24L01 and true for RF24L01P 
      bool p_variant; 
      //Fixed size of payloads 
      std::uint8_t payload_size; 
      //Whether dynamic payloads are enabled.
      bool dynamic_payloads_enabled; 
      //Last address set on pipe 0 for reading.
      std::uint8_t pipe0_reading_address[5]; 
      //The address width to use - 3,4 or 5 bytes.
      std::uint8_t addr_width;
      //Delay on cs
      std::uint8_t csDelay;

//typedef util::timer<std::uint_fast16_t> timer_type;
typedef util::timer<std::uint32_t> timer_type;
      timer_type        driver_wait;


    public:
      RF24();
      RF24(std::uint8_t _cepin, std::uint8_t _cspin);

      //Begin the operation of the chip.
      void begin(void);

      //Checks if the chip is connected to the SPI bus      
      bool isChipConnected();

      //Start listening on the pipes opened for reading.
      void startListening(void);

      //Stop listening for incoming messages, and switch to transmit mode.
      void stopListening(void);

      //Check whether there are bytes available to be read
      bool available(void);

      //Read the available payload
      void read( void* buf, std::uint8_t len );

      //Wire a payload to the destination.
      bool write( const void* buf, std::uint8_t len );

      //Open a pipe for writing via byte array. Old addressing format retained for compatibility.
      void openWritingPipe(const std::uint8_t *address);

      //Open a pipe for reading
      void openReadingPipe(std::uint8_t number, const std::uint8_t *address);

      virtual ~RF24();

      // Advanced Operation
      // ==================

      /*
      //Print a giant block of debugging information to stdout
      void printDetails(void);
      //Test whether there are bytes available to be read in the FIFO buffers. 
      bool available(uint8_t* pipe_num);
      //Check if the radio needs to be read. Can be used to prevent data loss
      bool rxFifoFull();      

      //Enter low-power mode
      void powerDown(void);
      //Leave low-power mode - required for normal radio operation after calling powerDown()
      void powerUp(void) ;
      //Write for single NOACK writes. Optionally disables acknowledgements/autoretries for a single write.
      bool write( const void* buf, uint8_t len, const bool multicast );
      // This will not block until the 3 FIFO buffers are filled with data.
      bool writeFast( const void* buf, uint8_t len );
      //WriteFast for single NOACK writes. Disables acknowledgements/autoretries for a single write.
      bool writeFast( const void* buf, uint8_t len, const bool multicast );
      //This function extends the auto-retry mechanism to any specified duration.
      bool writeBlocking( const void* buf, uint8_t len, uint32_t timeout );
      //This function should be called as soon as transmission is finished to
      // drop the radio back to STANDBY-I mode
      bool txStandBy();
      //This function allows extended blocking and auto-retries per a user defined timeout
      bool txStandBy(uint32_t timeout, bool startTx = 0);
      // Write an ack payload for the specified pipe
      void writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);
      //Determine if an ack payload was received in the most recent call to
      // write(). The regular available() can also be used.
      bool isAckPayloadAvailable(void);
*/


    };

  }
}

#endif //_HAL_RF24_EMBEDDED_H_
