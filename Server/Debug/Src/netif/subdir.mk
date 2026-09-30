################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/netif/ethernet.c \
../Src/netif/ethernetif.c 

OBJS += \
./Src/netif/ethernet.o \
./Src/netif/ethernetif.o 

C_DEPS += \
./Src/netif/ethernet.d \
./Src/netif/ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
Src/netif/%.o Src/netif/%.su Src/netif/%.cyclo: ../Src/netif/%.c Src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -c -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Device/ST/STM32N657xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-netif

clean-Src-2f-netif:
	-$(RM) ./Src/netif/ethernet.cyclo ./Src/netif/ethernet.d ./Src/netif/ethernet.o ./Src/netif/ethernet.su ./Src/netif/ethernetif.cyclo ./Src/netif/ethernetif.d ./Src/netif/ethernetif.o ./Src/netif/ethernetif.su

.PHONY: clean-Src-2f-netif

