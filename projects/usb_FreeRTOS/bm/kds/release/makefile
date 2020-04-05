################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include sources/subdir.mk
-include board/subdir.mk
-include FreeRTOS/port/subdir.mk
-include FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: dev_cdc_virtual_com_bm_frdmkl25z.elf secondary-outputs

# Tool invocations
dev_cdc_virtual_com_bm_frdmkl25z.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -T ../../../../../../../../../../platform/devices/MKL25Z4/linker/gcc/MKL25Z128xxx4_flash.ld -Xlinker --gc-sections -Wl,-Map,"dev_cdc_virtual_com_bm_frdmkl25z.map" -Xlinker -z  -Xlinker muldefs   -Xlinker --defsym=__ram_vector_table__=1  --specs=nano.specs          -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -Xlinker -static  -Xlinker --defsym=__stack_size__=0x0400  -Xlinker --defsym=__heap_size__=0x0400 -o "dev_cdc_virtual_com_bm_frdmkl25z.elf" -Xlinker --start-group $(OBJS) $(USER_OBJS) $(LIBS) -Xlinker --end-group
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(S_UPPER_DEPS) dev_cdc_virtual_com_bm_frdmkl25z.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
