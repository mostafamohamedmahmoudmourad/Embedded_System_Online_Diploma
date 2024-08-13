#@copyright : Mostafa
#
CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2 -std=c99
ASFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
LIBS=
As = $(wildcard *.s)
AsOBJ= $(As:.s=.o)
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o) $(AsOBJ)
Project_name= learn_in_depth_cortex_m3

all: $(Project_name).bin
	@echo "----------Build is Done-----------"

%.o: %.s
	$(CC)as.exe $(ASFLAGS) $< -o $@ 2> log

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(Project_name).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=output.map
	cp	$(Project_name).elf	$(Project_name).axf
$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm -f *.o *.elf *.bin

clean:
	rm -f *.elf *.bin