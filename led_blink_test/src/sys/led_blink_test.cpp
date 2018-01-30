/**
 * @file led_blink_test.cpp
 * @brief Turn on and off a LED.
 * @description Turn on and off a led on portb4 each second.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _LED_BLINK_TEST_EMBEDDED_2018_
#define _LED_BLINK_TEST_EMBEDDED_2018_

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace
{
  // Define a convenient local 32-bit timer type.
  typedef util::timer<std::uint32_t> timer_type;
}

int main()
{
  // Initialize the mcal.
  mcal::init();

  // Toggle led1 forever.
  for(;;)
  {
    led_b1.toggle();

    // Wait 1 second in a blocking delay.
    timer_type::blocking_delay(timer_type::seconds(1U));
  }
}

#endif //_LED_BLINK_TEST_EMBEDDED_2018_
