################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Bibliotecas/Documentos/Repositorios/KL25Z/drivers/gpio/src/gpio.c 

OBJS += \
./drivers_dev/gpio/src/gpio.o 

C_DEPS += \
./drivers_dev/gpio/src/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
drivers_dev/gpio/src/gpio.o: F:/Bibliotecas/Documentos/Repositorios/KL25Z/drivers/gpio/src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition\board" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\accelerometer\mma8451q\inc" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\accelerometer\mma8451q\src" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\arch" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\arch\clock" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\gpio\inc" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\gpio\src" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\i2c\inc" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\i2c\src" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\lcd_i2c\inc" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\lcd_i2c\src" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\tpm\inc" -I"F:\Bibliotecas\Documentos\Repositorios\KL25Z\drivers\tpm\src" -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition\source" -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition" -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition\drivers" -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition\CMSIS" -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition\utilities" -I"C:\Users\thiag\Documents\MCUXpressoIDE_11.1.1_3241\workspace\acquisition\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


