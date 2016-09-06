################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STemWin/Config/GUIConf.c \
../STemWin/Config/LCDConf_Lin_Template.c 

OBJS += \
./STemWin/Config/GUIConf.o \
./STemWin/Config/LCDConf_Lin_Template.o 

C_DEPS += \
./STemWin/Config/GUIConf.d \
./STemWin/Config/LCDConf_Lin_Template.d 


# Each subdirectory must supply rules for building sources it contributes
STemWin/Config/%.o: ../STemWin/Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F429xx -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../STemWin/inc -I../STemWin/Config -I../STemWin/Demo -I../STemWin/Font -I../Src -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


