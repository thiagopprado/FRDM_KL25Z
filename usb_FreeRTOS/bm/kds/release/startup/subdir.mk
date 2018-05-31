################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Freescale/KSDK_1.3.0/platform/devices/startup.c \
C:/Freescale/KSDK_1.3.0/platform/devices/MKL25Z4/startup/system_MKL25Z4.c 

S_UPPER_SRCS += \
C:/Freescale/KSDK_1.3.0/platform/devices/MKL25Z4/startup/gcc/startup_MKL25Z4.S 

OBJS += \
./startup/startup.o \
./startup/startup_MKL25Z4.o \
./startup/system_MKL25Z4.o 

C_DEPS += \
./startup/startup.d \
./startup/system_MKL25Z4.d 

S_UPPER_DEPS += \
./startup/startup_MKL25Z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup.o: C:/Freescale/KSDK_1.3.0/platform/devices/startup.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -D_DEBUG=0 -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/MKL25Z4 -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/video -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/MKL25Z4 -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/dma -I../../../../../../../../../../platform/system/inc -I../../../../../../../../../../platform/drivers/src/uart -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/startup_MKL25Z4.o: C:/Freescale/KSDK_1.3.0/platform/devices/MKL25Z4/startup/gcc/startup_MKL25Z4.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -x assembler-with-cpp -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/system_MKL25Z4.o: C:/Freescale/KSDK_1.3.0/platform/devices/MKL25Z4/startup/system_MKL25Z4.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -D_DEBUG=0 -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/MKL25Z4 -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/video -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/MKL25Z4 -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/dma -I../../../../../../../../../../platform/system/inc -I../../../../../../../../../../platform/drivers/src/uart -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


