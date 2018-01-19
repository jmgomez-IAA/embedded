COMPILE		= avr-c++
OBJCOPY 	= avr-objcopy
OBJDUMP 	= avr-objdump
SIZE		= avr-size
NM 		= avr-nm
AVRDUDE 	= avrdude
REMOVE 		= rm -f

#CPU Specific flags.
MCU 		= attiny85
F_CPU 		= 1000000

#Compiler flags.
CSTANDARD	= -std=c++11
CPPDEFS		= -DF_CPU=$(F_CPU)UL -mmcu=$(MCU)
CFLAGS		= -Wall -Wextra -pedantic -DF_CPU=$(F_CPU)UL  -mmcu=$(MCU) -fsigned-char -O2 -fno-exceptions
CPPFLAGS	= -std=c++11
CINCLUDES	= -Isrc -Isrc/mcal/at85 -I../util/STL/

#src/mcal/at85/mcal_cpu.cpp
#bin/mcal_cpu.o
SOURCES = src/mcal/mcal.cpp src/mcal/at85/mcal_irq.cpp src/mcal/at85/mcal_led.cpp src/sys/led_test.cpp 
OBJECTS = bin/mcal.o bin/mcal_irq.o bin/mcal_led.o bin/led_test.o

all : led_test.elf

bin/mcal.o	: src/mcal/mcal.cpp
	echo "Compile  : mcal.cpp to bin/mcal.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/mcal.cpp -o bin/mcal.o

bin/mcal_irq.o : src/mcal/at85/mcal_irq.cpp
	echo "Compile  : mcal_irq.cpp to bin/mcal_irq.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/at85/mcal_irq.cpp -o bin/mcal_irq.o

bin/mcal_led.o : src/mcal/at85/mcal_led.cpp
	echo "Compile  : mcal_led.cpp to bin/mcal_led.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/at85/mcal_led.cpp -o bin/mcal_led.o

bin/led_test.o : src/sys/led_test.cpp
	echo "Compile  : Compile led_test.cpp"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/sys/led_test.cpp -o bin/led_test.o

led_test.elf : $(OBJECTS)
	echo "Link     : objects to bin/led_test.elf"
	$(COMPILE) -x none -mrelax $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -Wl,--gc-sections  $(OBJECTS) -o bin/led_test.elf

info:
	$(SIZE) bin/load_test.elf

flash :
	echo "Flashing AVRDUDE: Locate Fuses to 1MHz clock."
	avr-objcopy -j .text -j .data -O ihex bin/chapter02_03.elf bin/chapter02_03.hex
	avrdude -P /dev/ttyACM0 -b 19200 -c avrisp -p t85 -U flash:w:bin/chapter02_03.hex:i


clean : 
	rm bin/*
