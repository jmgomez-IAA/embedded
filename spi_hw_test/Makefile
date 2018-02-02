COMPILE		= avr-c++
OBJCOPY 	= avr-objcopy
OBJDUMP 	= avr-objdump
SIZE		= avr-size
NM 		= avr-nm
AVRDUDE 	= avrdude
REMOVE 		= rm -f

#CPU Specific flags.
MCU 		= atmega328p
F_CPU 		= 8000000

#Compiler flags.
CSTANDARD	= -std=c++11
CPPDEFS		= -DF_CPU=$(F_CPU)UL -mmcu=$(MCU)
CFLAGS		= -Wall -Wextra -pedantic -DF_CPU=$(F_CPU)UL  -mmcu=$(MCU) -fsigned-char -O2 -fno-exceptions
CPPFLAGS	= -std=c++11
CINCLUDES	= -Isrc -Isrc/mcal/atmega328p -I. -Iutil/STL/ -Isrc/hal/RF24

#src/mcal/at85/mcal_cpu.cpp
#bin/mcal_cpu.o
SOURCES = src/mcal/mcal.cpp src/mcal/atmega328p/mcal_irq.cpp src/mcal/atmega328p/mcal_led.cpp src/mcal/atmega328p/mcal_gpt.cpp src/mcal/atmega328p/mcal_spi.cpp src/sys/spi_hw_test.cpp src/hal/RF24/RF24.cpp
OBJECTS = bin/mcal.o bin/mcal_irq.o bin/mcal_led.o bin/mcal_gpt.o bin/mcal_spi.o bin/hal_rf24 bin/spi_hw_test.o

all : spi_hw_test.elf

bin/mcal.o	: src/mcal/mcal.cpp
	echo "Compile  : mcal.cpp to bin/mcal.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/mcal.cpp -o bin/mcal.o

bin/mcal_irq.o : src/mcal/atmega328p/mcal_irq.cpp
	echo "Compile  : mcal_irq.cpp to bin/mcal_irq.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/atmega328p/mcal_irq.cpp -o bin/mcal_irq.o

bin/mcal_led.o : src/mcal/atmega328p/mcal_led.cpp
	echo "Compile  : mcal_led.cpp to bin/mcal_led.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/atmega328p/mcal_led.cpp -o bin/mcal_led.o

bin/mcal_gpt.o : src/mcal/atmega328p/mcal_gpt.cpp
	echo "Compile  : mcal_gpt.cpp to bin/mcal_gpt.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/atmega328p/mcal_gpt.cpp -o bin/mcal_gpt.o

bin/mcal_spi.o : src/mcal/atmega328p/mcal_spi.cpp
	echo "Compile  : mcal_gpt.cpp to bin/mcal_gpt.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/atmega328p/mcal_spi.cpp -o bin/mcal_spi.o

## Build the RF24 Library for ATMega328p

bin/hal_rf24.o : src/hal/RF24/RF24.cpp
	echo "Compile  : Build RF24 library object."
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/hal/RF24/RF24.cpp -o bin/hal_rf24.o

bin/spi_hw_test.o : src/sys/spi_hw_test.cpp
	echo "Compile  : Compile spi_hw_test.cpp"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/sys/spi_hw_test.cpp -o bin/spi_hw_test.o

spi_hw_test.elf : $(OBJECTS)
	echo "Link     : objects to bin/led_blink_test.elf"
	$(COMPILE) -x none -mrelax $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -Wl,--gc-sections  $(OBJECTS) -o bin/spi_hw_test.elf
	avr-objcopy -j .text -j .data -O ihex bin/spi_hw_test.elf bin/spi_hw_test.hex

info:
	$(SIZE) bin/load_test.elf

flash :
	echo "Flashing AVRDUDE: Locate Fuses to 1MHz clock."
	avrdude -P /dev/ttyUSB0 -b 57600 -c arduino -p m328p -U flash:w:bin/spi_hw_test.hex:i


clean : 
	rm bin/*
