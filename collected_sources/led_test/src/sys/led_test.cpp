/**
 * @file led_test.h
 * @brief LED example
 * @description Turn on a led on portb4.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _LED_TEST_EMBEDDED_2018_
#define _LED_TEST_EMBEDDED_2018_

#include <mcal/mcal.h>


int main()
{
mcal::init();


for (;;)
  {
led_b4.toggle();
}
}

#endif //_LED_TEST_EMBEDDED_2018_
