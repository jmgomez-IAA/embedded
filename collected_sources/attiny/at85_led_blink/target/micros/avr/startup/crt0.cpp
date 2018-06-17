///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// ATMEL(R) AVR(R) startup code.
// Completely written in C++ for Atmega328P by Chris.

#include <mcal/mcal.h>

asm volatile(".extern __initial_stack_pointer");

namespace crt
{
  void init_ram  () __attribute__((section(".startup")));
  void init_ctors() __attribute__((section(".startup")));
}

extern "C" void __my_startup() __attribute__((section(".startup"), used, noinline));

void __my_startup()
{
  // Load the SREG register.
  asm volatile("eor r1, r1");
  asm volatile("out 0x3F, r1");

  // Set the stack pointer.
  asm volatile("ldi r28, lo8(__initial_stack_pointer)");
  asm volatile("ldi r29, hi8(__initial_stack_pointer)");

  // Load the SPH register (stack pointer high).
  asm volatile("out 0x3E, r29");

  // Load the SPL register (stack pointer low).
  asm volatile("out 0x3D, r28");

  // This is an empty dummy in this project.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear non-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Call main (and never return).
  asm volatile("call main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::cpu::nop();
  }
}
