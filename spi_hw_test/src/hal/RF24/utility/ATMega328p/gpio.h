

/**
 * @file gpio.h
 * Class declaration for SPI helper files
 */

 /**
 * Example of gpio.h class declaration for GPIO portability
 *
 * @defgroup Porting_GPIO Porting: GPIO
 *
 * 
 * @{
 */
#ifndef __GPIO_WRAPPER_FOR_ARDUINO__
#define	__GPIO_WRAPPER_FOR_ARDUINO__

#include <cstdint>
#include <mcal/mcal.h>

/*
 * The number of the pin is refered to the pin on the board, not the port[A,B,C,D].
*/

class GPIO {
 public:
  /* Constants */
  static const int DIRECTION_OUT = 1;
  static const int DIRECTION_IN = 0;
	
  static const int OUTPUT_HIGH = 1;
  static const int OUTPUT_LOW = 0;
		
  GPIO(){};
	
  /**
   * Similar to Arduino pinMode(pin,mode);
   * @param port
   * @param DDR
   */
  static void open(int port, int DDR);
  /**
   * 
   * @param port
   */
  static void close(int port){};
  /**
   * Similar to Arduino digitalRead(pin);
   * @param port
   * @param value
   */
  static int read(int port){};
  /**
   * Similar to Arduino digitalWrite(pin,state);
   * @param port
   * @param value
   */	
  static void write(int port,int value);	
	
  virtual ~GPIO();

};

#endif // __GPIO_WRAPPER_FOR_ARDUINO__
/*@}*/	
