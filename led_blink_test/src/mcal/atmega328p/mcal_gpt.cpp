/**
 * @file mcal_gpt.cpp
 * @brief General purpose timer abstraction layer.
 * @description Provides functions to initialize and 
 * control the general purpose timer of the attiny85.
 * Include the now and get_time_elapsed for the std chrono class.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

/**
 * System clock 1 MHz.
 */

#include <avr/interrupt.h>
#include <mcal_gpt.h>
#include <mcal_reg_access.h>

namespace
{
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init;

    return is_init;
  }
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Clear the timer0 overflow flag.
    mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tifr0, 0x01U>::reg_set();

    // Enable the timer0 overflow interrupt.
    mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::timsk0, 0x01U>::reg_set();

    // Set the timer0 clock source to f_osc/8 = 2MHz and begin counting.
    mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tccr0b, 0x02U>::reg_set();

    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }  
}

//Attiny
//ISR(TIM0_OVF_vect)
//ATMega328p
ISR(TIMER0_OVF_vect)
//void TIMER0_OVF0()
{
  // Increment the 32-bit system tick with 0x80, representing 128 microseconds.
  system_tick += static_cast<std::uint8_t>(0x80U);
}

//Provide the function get_time_elapsed used by chrono.
mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Return the system tick using a multiple read to ensure
  // data consistency of the high-byte of the system tick.

  typedef std::uint8_t timer_address_type;
  typedef std::uint8_t timer_register_type;

  // Do the first read of the timer0 counter and the system tick.
  const timer_register_type tim0_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tcnt0>::reg_get();
 
  // Read the system tick.
  const mcal::gpt::value_type sys_tick_1 = system_tick;

  // Do the second read of the timer0 counter and the system tick.
  const timer_register_type tim0_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tcnt0>::reg_get();

  // Perform the consistency check and obtain the consistent microsecond tick.
  const mcal::gpt::value_type consistent_microsecond_tick
    = ((tim0_cnt_2 >= tim0_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | std::uint8_t(tim0_cnt_1 >> 1U))
                                  : mcal::gpt::value_type(system_tick | std::uint8_t(tim0_cnt_2 >> 1U)));

  return (gpt_is_initialized() ? consistent_microsecond_tick : mcal::gpt::value_type(0U));
  
}


