/**
 * @file hal_hm10.h
 * @brief HM10 BLE abstraction layer.
 * @description Provides functions to initialize and 
 * control the HM10 BLE module.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _HAL_HM10_EMBEDDED_H_
#define _HAL_HM10_EMBEDDED_H_

#include <cstdint>
#include <array>

namespace hal
{
namespace hm10
{
  constexpr std::array<std::uint8_t, 2U> test_command{
    { 'A', 'T'}
  };
}

}

#endif //_HAL_HM10_EMBEDDED_H_

