################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Tx_Loopback_Mode.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Tx_Loopback_Mode.list \

OBJCOPY_BIN += \
Tx_Loopback_Mode.bin \


# All Target
all: Tx_Loopback_Mode.elf secondary-outputs

# Tool invocations
Tx_Loopback_Mode.elf: $(OBJS) $(USER_OBJS) E:\Embedded\ System\Basic\Embedded_System_Online_Diploma\CAN_Protocol\CAN_Protocol\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Tx_Loopback_Mode.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Embedded System\Basic\Embedded_System_Online_Diploma\CAN_Protocol\CAN_Protocol\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Tx_Loopback_Mode.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Tx_Loopback_Mode.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Tx_Loopback_Mode.list"
	@echo 'Finished building: $@'
	@echo ' '

Tx_Loopback_Mode.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Tx_Loopback_Mode.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
