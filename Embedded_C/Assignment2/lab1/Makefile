#@copyright : Mostafa
CC=arm-none-eabi-
CFLAGS=-g -mcpu=arm926ej-s
INCS=-I .
LIBS=
As = $(wildcard *.s)
AsOBJ= $(As:.s=.o)
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
Project_name= learn-in-depth

all: $(Project_name).bin
	@echo "----------Build is Done-----------"


%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

%.o: %.s
	$(CC)as.exe   $(CFLAGS) $< -o $@  2> log



$(Project_name).elf:  $(OBJ)  $(AsOBJ) startup.o    
	$(CC)ld.exe -T linker_script.ld $(LIBS)  $(OBJ)  startup.o     -o $@ -Map=output.map

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm -f *.o *.elf *.bin

clean:
	rm -f *.elf *.bin
