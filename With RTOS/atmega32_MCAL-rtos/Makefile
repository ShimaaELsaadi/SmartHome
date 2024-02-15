# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory
PROJ_DIR := $(realpath $(CURDIR))
PROJ_NAME = smartHome

PROJ_SRC =  $(addprefix APP/,$(addsuffix  .c,$(PROJ_NAME)))
PROJ_OBJ = $(patsubst %.c,%.o,$(PROJ_SRC))

CC = avr-gcc
LD = avr-ld
OBJCOPY = avr-objcopy
OBJSIZE = avr-size

# Name of the final executable
TARGET = $(addsuffix .elf, $(PROJ_NAME))
HEX_FILE = $(patsubst %.elf,%.hex,$(TARGET))
BUILDDIR := Build

DIRS =		MCAL/DIO 		\
			MCAL/WDT		\
			MCAL/ADC 		\
			MCAL/EEPROM		\
			MCAL/EXTI 		\
			MCAL/GI 		\
			MCAL/SPI		\
			MCAL/TIMER	 	\
			MCAL/TWI 		\
			MCAL/UART 		\
			HAL/LCD			\
			HAL/Keypad		\
			HAL/SRV			\
			RTOS/portable_gcc_atmega32 			\
			RTOS/portable_gcc_atmega32/mem_mang	\
			RTOS/source

SOURCES := $(foreach i , $(DIRS) , $(wildcard $(i)/*.c))
OBJECTS := $(foreach i, $(SOURCES), $(patsubst %.c,%.o,$(i)))
MKDIR := $(foreach i , $(DIRS) , $(addprefix $(BUILDDIR)/, $(i)))

IPATH = 	utils			\
			MCAL/EEPROM		\
			MCAL/ADC 		\
			MCAL/DIO		\
			MCAL/EXTI 		\
			MCAL/GI 		\
			MCAL/SPI		\
			MCAL/TIMER		\
			MCAL/TWI 		\
			MCAL/UART 		\
			MCAL/WDT 		\
			HAL/LCD 		\
			HAL/Keypad 		\
			HAL/SRV 		\
			RTOS/portable_gcc_atmega32		\
			RTOS/include	

INCLUDE = $(foreach dir, $(IPATH), $(addprefix -I, $(dir)))

MCU = atmega32
F_CPU = 16000000UL

WARNING = -Wunused-function -Wswitch -Wunused-variable -Wreturn-type
NO_WARNING = -Wno-unused-function -Wno-switch -Wno-unused-variable -Wno-return-type

CFLAGS := -mmcu=$(MCU) -Wall -Os -DF_CPU=$(F_CPU) $(INCLUDE) $(NO_WARNING)
LDFLAGS := $(CFLAGS)

all:$(TARGET) $(HEX_FILE)
	$(OBJSIZE) -C --mcu=$(MCU) $(TARGET)

$(TARGET): $(PROJ_OBJ) $(OBJECTS)
	@echo "Linking $@"
	@$(CC) $^ -o $@ $(LDFLAGS)

$(PROJ_OBJ): $(PROJ_SRC)
	@echo "Building $<"
	@$(CC) -c $< -o $@ $(CFLAGS)

$(HEX_FILE): $(TARGET)
	@echo "Creating Hex File $(HEX_FILE)"
	@$(OBJCOPY) -j .text -j .data -O ihex $(TARGET) $@

########################################################################
# using static pattern rule to compile for now
# TODO : using generate rule method
$(OBJECTS):%.o:%.c
	@echo "Building $<"
	@$(CC) -c $< -o $@ $(CFLAGS)
########################################################################

flash: $(HEX_FILE)
	avrdude -p m32 -c usbasp -U flash:w:$<


test_connection:
	avrdude -p m32 -c usbasp


clean:
	@rm $(PROJ_OBJ)
	@rm $(OBJECTS)
	@rm $(TARGET)
	@rm $(HEX_FILE)
	


# Used in Debuging Makefile By printing variables names
print-%: 
	@echo $* = $($*)