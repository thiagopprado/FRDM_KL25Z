################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/gpio.c \
../Sources/main.c 

OBJS += \
./Sources/gpio.o \
./Sources/main.o 

C_DEPS += \
./Sources/gpio.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL25Z4/include" -I"C:\Freescale\KSDK_1.3.0/platform/devices" -I"C:\Freescale\KSDK_1.3.0/platform/devices/MKL25Z4/startup" -I"C:\Freescale\KSDK_1.3.0/platform/devices/MKL25Z4/startup/gcc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


