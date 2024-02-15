################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../carrera_tc/main.cpp 

OBJS += \
./carrera_tc/main.o 

CPP_DEPS += \
./carrera_tc/main.d 


# Each subdirectory must supply rules for building sources it contributes
carrera_tc/%.o carrera_tc/%.su carrera_tc/%.cyclo: ../carrera_tc/%.cpp carrera_tc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-carrera_tc

clean-carrera_tc:
	-$(RM) ./carrera_tc/main.cyclo ./carrera_tc/main.d ./carrera_tc/main.o ./carrera_tc/main.su

.PHONY: clean-carrera_tc

