################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/thiag/Dropbox/IC/KL25Z/lib/gpio_x.c 

OBJS += \
./lib/gpio_x.o 

C_DEPS += \
./lib/gpio_x.d 


# Each subdirectory must supply rules for building sources it contributes
lib/gpio_x.o: C:/Users/thiag/Dropbox/IC/KL25Z/lib/gpio_x.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -I"C:\Freescale\KSDK_1.3.0\rtos\FreeRTOS\include" -I"C:\Users\thiag\Dropbox\IC\KL25Z\lib" -I"C:\Freescale\KSDK_1.3.0\rtos\FreeRTOS\port\gcc" -I"C:\Freescale\KSDK_1.3.0\rtos\FreeRTOS\config\KL25Z4\gcc" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL25Z4/include" -I"C:\Freescale\KSDK_1.3.0/rtos/FreeRTOS/src" -I"C:\Freescale\KSDK_1.3.0/rtos/FreeRTOS/include" -I"C:\Freescale\KSDK_1.3.0/rtos/FreeRTOS/port/gcc" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/drivers/nio_serial" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/string" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/config/common" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx_stdlib/source/include" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/kernel" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/src" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/bsp" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/drivers/nio_serial/src" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx_stdlib/source/strings" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/psp/cortex_m" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/drivers/nio_tty/src" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/drivers/nio_dummy/src" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/psp/cortex_m/cpu" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/psp/cortex_m/core/M0" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/fs" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx_stdlib/source/stdio" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/drivers/nio_tty" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/psp/cortex_m/compiler/gcc_arm" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/nio/drivers/nio_dummy" -I"C:\Freescale\KSDK_1.3.0/rtos/mqx/mqx/source/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


