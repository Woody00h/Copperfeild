################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STemWin/Font/Calibri73.c \
../STemWin/Font/Calibri_11_Bold.c \
../STemWin/Font/Calibri_13_Bold.c \
../STemWin/Font/Calibri_15_Bold.c \
../STemWin/Font/Calibri_19_Bold.c \
../STemWin/Font/Calibri_99.c \
../STemWin/Font/Calibri_9_Bold.c 

OBJS += \
./STemWin/Font/Calibri73.o \
./STemWin/Font/Calibri_11_Bold.o \
./STemWin/Font/Calibri_13_Bold.o \
./STemWin/Font/Calibri_15_Bold.o \
./STemWin/Font/Calibri_19_Bold.o \
./STemWin/Font/Calibri_99.o \
./STemWin/Font/Calibri_9_Bold.o 

C_DEPS += \
./STemWin/Font/Calibri73.d \
./STemWin/Font/Calibri_11_Bold.d \
./STemWin/Font/Calibri_13_Bold.d \
./STemWin/Font/Calibri_15_Bold.d \
./STemWin/Font/Calibri_19_Bold.d \
./STemWin/Font/Calibri_99.d \
./STemWin/Font/Calibri_9_Bold.d 


# Each subdirectory must supply rules for building sources it contributes
STemWin/Font/%.o: ../STemWin/Font/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F429xx -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../STemWin/inc -I../STemWin/Config -I../STemWin/Demo -I../STemWin/Font -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


