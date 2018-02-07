/* 
 * File:   compatiblity.h
 * Author: purinda
 *
 * Created on 24 June 2012, 3:08 PM
 */

 /**
 * @file compatibility.h
 * Class declaration for SPI helper files
 */

 /**
 * Example of compatibility.h class declaration for timing functions portability
 *
 * @defgroup Porting_Timing Porting: Timing
 *
 * 
 * @{
 */
 
#ifndef COMPATIBLITY_H
#define	COMPATIBLITY_H

#ifdef	__cplusplus
extern "C" {
#endif
	
  /*
#include <stddef.h>
#include <time.h>
#include <sys/time.h>
  */
#include <cstdint>
#include <util/utility/util_time.h> 

typedef util::timer<std::uint32_t> timer_type;

  void __msleep(std::uint8_t milisec){
    timer_type::blocking_delay(timer_type::milliseconds(milisec));
  }

  void __usleep(std::uint8_t microsec){
    timer_type::blocking_delay(timer_type::microseconds(microsec));
  }

  void __start_timer() {};
  long __millis() {return 0;};

#ifdef	__cplusplus
}
#endif

#endif	/* COMPATIBLITY_H */

/*@}*/	
