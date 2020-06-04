################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers_dev/tpm/src/subdir.mk
-include drivers_dev/lcd_i2c/src/subdir.mk
-include drivers_dev/i2c/src/subdir.mk
-include drivers_dev/gpio/src/subdir.mk
-include drivers_dev/arch/clock/subdir.mk
-include drivers_dev/accelerometer/mma8451q/src/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: acquisition.axf

# Tool invocations
acquisition.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="acquisition.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m0plus -mthumb -T acquisition_Debug.ld -o "acquisition.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) acquisition.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "acquisition.axf"; # arm-none-eabi-objcopy -v -O binary "acquisition.axf" "acquisition.bin" ; # checksum -p MKL25Z128xxx4 -d "acquisition.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
