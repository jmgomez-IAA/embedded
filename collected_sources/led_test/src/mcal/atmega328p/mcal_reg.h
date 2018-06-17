/**
 * @file mcal_reg.h
 * @brief ATMega328p register memory map.
 * @description Defines the ATMega328p registers memory map.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_REG_EMBEDDED_H_
  #define _MCAL_REG_EMBEDDED_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // ARduino I/O register offset
      constexpr std::uint8_t sfr_offset = 0x20U;

      // Bit-position values.
      constexpr std::uint8_t bval0  = 1U;
      constexpr std::uint8_t bval1  = 1U << 1U;
      constexpr std::uint8_t bval2  = 1U << 2U;
      constexpr std::uint8_t bval3  = 1U << 3U;
      constexpr std::uint8_t bval4  = 1U << 4U;
      constexpr std::uint8_t bval5  = 1U << 5U;
      constexpr std::uint8_t bval6  = 1U << 6U;
      constexpr std::uint8_t bval7  = 1U << 7U;

      // Port registers
      constexpr std::uint8_t ddrb   = 0x24U + sfr_offset;
      constexpr std::uint8_t portb  = 0x25U + sfr_offset;

      // Timer registers
      constexpr std::uint8_t gtccr  = 0x43U + sfr_offset;
      constexpr std::uint8_t tifr0  = 0x35U + sfr_offset;
      constexpr std::uint8_t tifr1  = 0x36U + sfr_offset;
      constexpr std::uint8_t tifr2  = 0x37U + sfr_offset;

      constexpr std::uint8_t tccr0a = 0x44U + sfr_offset;
      constexpr std::uint8_t tccr0b = 0x45U + sfr_offset;
      constexpr std::uint8_t tcnt0  = 0x46U + sfr_offset;
      constexpr std::uint8_t ocr0a  = 0x47U + sfr_offset;
      constexpr std::uint8_t ocr0b  = 0x48U + sfr_offset;

      constexpr std::uint8_t timsk0 = 0x6EU + sfr_offset;
      constexpr std::uint8_t timsk1 = 0x6FU + sfr_offset;
      constexpr std::uint8_t timsk2 = 0x70U + sfr_offset;

      // SPI registers
      constexpr std::uint8_t SPCR0 = 0x4CU + sfr_offset;
      constexpr std::uint8_t SPSR0 = 0x4DU + sfr_offset;
      constexpr std::uint8_t SPDR0 = 0x4EU + sfr_offset;

      // USI registers
      //      constexpr std::uint8_t usidr = 0x0FU + sfr_offset;
      //constexpr std::uint8_t usibr = 0x10U + sfr_offset;
      //constexpr std::uint8_t usisr = 0x0EU + sfr_offset;
      //constexpr std::uint8_t usicr = 0x0DU + sfr_offset;
      
    }
  }
#endif // _MCAL_REG_EMBEDDED_H_
