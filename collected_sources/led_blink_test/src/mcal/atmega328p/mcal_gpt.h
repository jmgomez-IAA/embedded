/**
 * @file mcal_gpt.h
 * @brief General purpose timer abstraction layer.
 * @description Provides functions to initialize and 
 * control the general purpose timer of the attiny85.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_GPT_EMBEDDED_H_
  #define _MCAL_GPT_EMBEDDED_H_

#include <chrono>
#include <cstdint>

namespace util
{
  template <typename unsigned_tick_type>
  class timer;
}

namespace mcal
{
  namespace gpt
  {
    typedef void config_type;
    typedef std::uint32_t value_type;

    void init(const config_type*);

    class secure final
    {
      
      //    private:
      static value_type get_time_elapsed();
      friend std::chrono::high_resolution_clock::time_point std::chrono::high_resolution_clock::now();
      
      template <typename unsigned_tick_type>
          friend class util::timer;
      
    };

  }
}

#endif // _MCAL_GPT_EMBEDDED_H_

