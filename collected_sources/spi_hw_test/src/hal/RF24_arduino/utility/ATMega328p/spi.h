/**
 * @file spi.h
 * Class declaration for SPI helper files
 */

 /**
 * Example of spi.h class declaration for SPI portability
 *
 * @defgroup Porting_SPI Porting: SPI
 *
 * 
 * @{
 */

/*
#include <string>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h> 
*/

#include <mcal/mcal.h>
#include <cstdint>
//#include <cstddef>

#ifndef  _HAL_RF24_SPI_H_
#define  _HAL_RF24_SPI_H_

class SPI
{
 public:

/**
	* SPI constructor
	*/	 
  SPI() : mode(0), bits(0), speed(0) {};
	
	/**
	* Start SPI
	*/
  void begin(std::uint8_t busNo) {};
	
	/**
	* Transfer a single byte
	* @param tx_ Byte to send
	* @return Data returned via spi
	*/
  std::uint8_t transfer(std::uint8_t tx_);
	
	/**
	* Transfer a buffer of data
	* @param tbuf Transmit buffer
	* @param rbuf Receive buffer
	* @param len Length of the data
	*/
  void transfernb(std::std_uint8_t* tbuf, std::uint8_t* rbuf, std::uint32_t len){};
  
	/**
	* Transfer a buffer of data without an rx buffer
	* @param buf Pointer to a buffer of data
	* @param len Length of the data
	*/	
  void transfern(std::uint8_t* buf, std::uint32_t len){};
	
  virtual ~SPI();

 private:
  /** Default SPI device */
  std::uint8_t device;
  /** SPI Mode set */
  std::uint8_t mode;
  /** word size*/
  std::uint8_t bits;
  /** Set SPI speed*/
  std::uint32_t speed;
  //  int fd;
};

#endif  //_HAL_RF24_SPI_H_
/*@}*/
