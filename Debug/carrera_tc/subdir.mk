################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../carrera_tc/Init.c \
../carrera_tc/decoder.c \
../carrera_tc/delays.c \
../carrera_tc/eeprom.c \
../carrera_tc/handlers.c \
../carrera_tc/variable.c \
../carrera_tc/version.c 

CPP_SRCS += \
../carrera_tc/main.cpp 

C_DEPS += \
./carrera_tc/Init.d \
./carrera_tc/decoder.d \
./carrera_tc/delays.d \
./carrera_tc/eeprom.d \
./carrera_tc/handlers.d \
./carrera_tc/variable.d \
./carrera_tc/version.d 

OBJS += \
./carrera_tc/Init.o \
./carrera_tc/decoder.o \
./carrera_tc/delays.o \
./carrera_tc/eeprom.o \
./carrera_tc/handlers.o \
./carrera_tc/main.o \
./carrera_tc/variable.o \
./carrera_tc/version.o 

CPP_DEPS += \
./carrera_tc/main.d 


# Each subdirectory must supply rules for building sources it contributes
carrera_tc/%.o carrera_tc/%.su carrera_tc/%.cyclo: ../carrera_tc/%.c carrera_tc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
carrera_tc/%.o carrera_tc/%.su carrera_tc/%.cyclo: ../carrera_tc/%.cpp carrera_tc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-carrera_tc

clean-carrera_tc:
	-$(RM) ./carrera_tc/Init.cyclo ./carrera_tc/Init.d ./carrera_tc/Init.o ./carrera_tc/Init.su ./carrera_tc/decoder.cyclo ./carrera_tc/decoder.d ./carrera_tc/decoder.o ./carrera_tc/decoder.su ./carrera_tc/delays.cyclo ./carrera_tc/delays.d ./carrera_tc/delays.o ./carrera_tc/delays.su ./carrera_tc/eeprom.cyclo ./carrera_tc/eeprom.d ./carrera_tc/eeprom.o ./carrera_tc/eeprom.su ./carrera_tc/handlers.cyclo ./carrera_tc/handlers.d ./carrera_tc/handlers.o ./carrera_tc/handlers.su ./carrera_tc/main.cyclo ./carrera_tc/main.d ./carrera_tc/main.o ./carrera_tc/main.su ./carrera_tc/variable.cyclo ./carrera_tc/variable.d ./carrera_tc/variable.o ./carrera_tc/variable.su ./carrera_tc/version.cyclo ./carrera_tc/version.d ./carrera_tc/version.o ./carrera_tc/version.su

.PHONY: clean-carrera_tc

