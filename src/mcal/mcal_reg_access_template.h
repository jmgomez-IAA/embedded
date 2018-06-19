/**
 * @file mcal_reg_access_template.h
 * @brief Memory Mapped Register Access.
 * @description Provides functions to access to the 
 * memory mapped register of the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_REG_ACCESS_TEMPLATE_EMBEDDED_H_
  #define _MCAL_REG_ACCESS_TEMPLATE_EMBEDDED_H_

namespace mcal
{
  namespace reg
  {
    template <typename register_address_type,
      typename register_value_type,
      const register_address_type address,
      const register_value_type value = static_cast<register_value_type>(0); 

    struct access
    {
      static void     reg_set() { *reinterpret_cast<volatile register_value_type*>(address)  = value; }
      static void     reg_and() { *reinterpret_cast<volatile register_value_type*>(address) &= value; }
      static void     reg_or () { *reinterpret_cast<volatile register_value_type*>(address) |= value; }
      static void     reg_not() { *reinterpret_cast<volatile register_value_type*>(address) &= register_value_type(~value); }
      static register_value_type reg_get() { return *reinterpret_cast<volatile register_value_type*>(address); }   
    };

  }
}

#endif //_MCAL_REG_ACCESS_TEMPLATE_EMBEDDED_H_
