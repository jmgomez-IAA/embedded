PREFIX		= 

COMPILE		= $(PREFIX)c++
OBJCOPY 	= $PREFIX)objcopy
OBJDUMP 	= $(PREIX)objdump
SIZE		= $PREFIX)size
NM 		= $PREFIX)nm
AVRDUDE 	= avrdude
REMOVE 		= rm -f

#CPU Specific flags.
MCU 		=
F_CPU 		= 

#Compiler flags.
CSTANDARD	= -std=c++11
CPPDEFS		= 
CFLAGS		= -Wall -Wextra -pedantic -fsigned-char -O2 -fno-exceptions
CPPFLAGS	= -std=c++11
CINCLUDES	= -Isrc/comm/

SOURCES = src/sys/start/comms_linux_framework.cpp
OBJECTS = build/comms_linux_framework.o
BIN_PATH = bin

all : comms.elf

$(OBJECTS)	: $(SOURCES)
	echo "Compile  : comms Linux FrameWork"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c $(SOURCES) -o $(OBJECTS)

comms.elf : $(OBJECTS)
	echo "Link     : objects to bin/comms.elf"
	$(COMPILE)  $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -Wl,--gc-sections  $(OBJECTS) -o bin/comms.elf

docu:
	java -jar scripts/plantuml.jar doc/images/spw_if.uml 	

clear : 
	rm bin/* build/*
