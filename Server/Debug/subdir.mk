################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup_stm32n657xx.s \
../startup_stm32n657xx_fsbl.s 

OBJS += \
./startup_stm32n657xx.o \
./startup_stm32n657xx_fsbl.o 

S_DEPS += \
./startup_stm32n657xx.d \
./startup_stm32n657xx_fsbl.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.s subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m55 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean--2e-

clean--2e-:
	-$(RM) ./startup_stm32n657xx.d ./startup_stm32n657xx.o ./startup_stm32n657xx_fsbl.d ./startup_stm32n657xx_fsbl.o

.PHONY: clean--2e-

