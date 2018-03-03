///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include "util_static_allocator.h"

void* util::static_allocator_base::do_allocate(const size_type size)
{
  static volatile std::uint8_t  buffer[static_allocator_base::buffer_size];
  static volatile std::uint8_t* get_ptr = buffer;

  // Get the newly allocated pointer.
  volatile std::uint8_t* p = get_ptr;

  // Does this allocation overflow the top of the buffer?
  const bool is_overflow = ((get_ptr + size) >= (buffer + static_allocator_base::buffer_size));

  // Increment the pointer for next time.
  // But only do this if the buffer does *not* overflow.
  if(is_overflow)
  {
    // TBD: Is any sensible error reaction possible here?
  }
  else
  {
    get_ptr += size;
  }

  return static_cast<void*>(const_cast<std::uint8_t*>(p));
}
