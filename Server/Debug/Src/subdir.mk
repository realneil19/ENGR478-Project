################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c 

OBJS += \
./Src/main.o 

C_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -c -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Device/ST/STM32N657xx/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Driver" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc/netif" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc" -O0 -ffunction-sections -fdata-sections -Wall -v -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su

.PHONY: clean-Src

