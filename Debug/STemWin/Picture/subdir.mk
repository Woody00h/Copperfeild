################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STemWin/Picture/AeraMax\ Pro\ Logo\ QR.c \
../STemWin/Picture/Brightness\ Icon\ Black.c \
../STemWin/Picture/FramewinDLG.c \
../STemWin/Picture/Products_Standard_Filter.c \
../STemWin/Picture/WindowDLG.c 

OBJS += \
./STemWin/Picture/AeraMax\ Pro\ Logo\ QR.o \
./STemWin/Picture/Brightness\ Icon\ Black.o \
./STemWin/Picture/FramewinDLG.o \
./STemWin/Picture/Products_Standard_Filter.o \
./STemWin/Picture/WindowDLG.o 

C_DEPS += \
./STemWin/Picture/AeraMax\ Pro\ Logo\ QR.d \
./STemWin/Picture/Brightness\ Icon\ Black.d \
./STemWin/Picture/FramewinDLG.d \
./STemWin/Picture/Products_Standard_Filter.d \
./STemWin/Picture/WindowDLG.d 


# Each subdirectory must supply rules for building sources it contributes
STemWin/Picture/AeraMax\ Pro\ Logo\ QR.o: ../STemWin/Picture/AeraMax\ Pro\ Logo\ QR.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F429xx -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../STemWin/inc -I../STemWin/Config -I../STemWin/Demo -I../STemWin/Font -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"STemWin/Picture/AeraMax Pro Logo QR.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

STemWin/Picture/Brightness\ Icon\ Black.o: ../STemWin/Picture/Brightness\ Icon\ Black.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F429xx -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../STemWin/inc -I../STemWin/Config -I../STemWin/Demo -I../STemWin/Font -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"STemWin/Picture/Brightness Icon Black.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

STemWin/Picture/%.o: ../STemWin/Picture/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F429xx -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../STemWin/inc -I../STemWin/Config -I../STemWin/Demo -I../STemWin/Font -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


