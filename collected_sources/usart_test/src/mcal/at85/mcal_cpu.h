/**
 * @file mcal_cpu.h
 * @brief Microcontroller CPU abstraction.
 * @description Provides functions access the CPU.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_CPU_EMBEDDED_2018_
#define _MCAL_CPU_EMBEDDED_2018_

namespace mcal
{
namespace cpu
{
inline void nop() { asm volatile ("nop"); }
}
}

#endif  _MCAL_CPU_EMBEDDED_2018_
