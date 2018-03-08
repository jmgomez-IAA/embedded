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
#F_CPU		= 16000000

#Compiler flags.
CSTANDARD	= -std=c++11
CPPDEFS		= -DF_CPU=$(F_CPU)UL -mmcu=$(MCU)
CFLAGS		= -Wall -Wextra -pedantic -DF_CPU=$(F_CPU)UL  -mmcu=$(MCU) -fsigned-char -O2 -fno-exceptions
CPPFLAGS	= -std=c++11
CINCLUDES	= -Isrc -Isrc/mcal/atmega328p -I. -Iutil/STL/

SOURCES = src/mcal/mcal.cpp src/mcal/atmega328p/mcal_irq.cpp src/mcal/atmega328p/mcal_led.cpp src/mcal/atmega328p/mcal_gpt.cpp src/mcal/atmega328p/mcal_usart.cpp

OBJECTS = bin/mcal.o bin/mcal_irq.o bin/mcal_led.o bin/mcal_usart.o bin/mcal_gpt.o bin/usart_test.o

all : usart_hello_test.elf

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

bin/mcal_usart.o : src/mcal/atmega328p/mcal_usart.cpp
	echo "Compile  : mcal_usart.cpp to bin/mcal_usart.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/atmega328p/mcal_usart.cpp -o bin/mcal_usart.o

bin/usart_test.o : src/sys/usart_test.cpp
	echo "Compile  : Compile usart_test.cpp"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/sys/usart_test.cpp -o bin/usart_test.o

usart_hello_test.elf : $(OBJECTS)
	echo "Link     : objects to bin/usart_hello_test.elf"
	$(COMPILE) -x none -mrelax $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -Wl,--gc-sections  $(OBJECTS) -o bin/usart_hello_test.elf
	avr-objcopy -j .text -j .data -O ihex bin/usart_hello_test.elf bin/usart_hello_test.hex

info:
	$(SIZE) bin/usart_hello_test.elf

flash :
	echo "Flashing AVRDUDE: Locate Fuses to 1MHz clock."
	avrdude -P /dev/ttyUSB0 -b 57600 -c arduino -p m328p -U flash:w:bin/usart_hello_test.hex:i
#	avrdude -P /dev/ttyACM0 -b 115200 -c arduino -p m328p -U flash:w:bin/usart_hello_test.hex:i

clean : 
	rm bin/*
