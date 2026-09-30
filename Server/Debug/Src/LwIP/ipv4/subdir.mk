################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LwIP/ipv4/acd.c \
../Src/LwIP/ipv4/autoip.c \
../Src/LwIP/ipv4/dhcp.c \
../Src/LwIP/ipv4/etharp.c \
../Src/LwIP/ipv4/icmp.c \
../Src/LwIP/ipv4/igmp.c \
../Src/LwIP/ipv4/ip4.c \
../Src/LwIP/ipv4/ip4_addr.c \
../Src/LwIP/ipv4/ip4_frag.c 

OBJS += \
./Src/LwIP/ipv4/acd.o \
./Src/LwIP/ipv4/autoip.o \
./Src/LwIP/ipv4/dhcp.o \
./Src/LwIP/ipv4/etharp.o \
./Src/LwIP/ipv4/icmp.o \
./Src/LwIP/ipv4/igmp.o \
./Src/LwIP/ipv4/ip4.o \
./Src/LwIP/ipv4/ip4_addr.o \
./Src/LwIP/ipv4/ip4_frag.o 

C_DEPS += \
./Src/LwIP/ipv4/acd.d \
./Src/LwIP/ipv4/autoip.d \
./Src/LwIP/ipv4/dhcp.d \
./Src/LwIP/ipv4/etharp.d \
./Src/LwIP/ipv4/icmp.d \
./Src/LwIP/ipv4/igmp.d \
./Src/LwIP/ipv4/ip4.d \
./Src/LwIP/ipv4/ip4_addr.d \
./Src/LwIP/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
Src/LwIP/ipv4/%.o Src/LwIP/ipv4/%.su Src/LwIP/ipv4/%.cyclo: ../Src/LwIP/ipv4/%.c Src/LwIP/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -c -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Device/ST/STM32N657xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-LwIP-2f-ipv4

clean-Src-2f-LwIP-2f-ipv4:
	-$(RM) ./Src/LwIP/ipv4/acd.cyclo ./Src/LwIP/ipv4/acd.d ./Src/LwIP/ipv4/acd.o ./Src/LwIP/ipv4/acd.su ./Src/LwIP/ipv4/autoip.cyclo ./Src/LwIP/ipv4/autoip.d ./Src/LwIP/ipv4/autoip.o ./Src/LwIP/ipv4/autoip.su ./Src/LwIP/ipv4/dhcp.cyclo ./Src/LwIP/ipv4/dhcp.d ./Src/LwIP/ipv4/dhcp.o ./Src/LwIP/ipv4/dhcp.su ./Src/LwIP/ipv4/etharp.cyclo ./Src/LwIP/ipv4/etharp.d ./Src/LwIP/ipv4/etharp.o ./Src/LwIP/ipv4/etharp.su ./Src/LwIP/ipv4/icmp.cyclo ./Src/LwIP/ipv4/icmp.d ./Src/LwIP/ipv4/icmp.o ./Src/LwIP/ipv4/icmp.su ./Src/LwIP/ipv4/igmp.cyclo ./Src/LwIP/ipv4/igmp.d ./Src/LwIP/ipv4/igmp.o ./Src/LwIP/ipv4/igmp.su ./Src/LwIP/ipv4/ip4.cyclo ./Src/LwIP/ipv4/ip4.d ./Src/LwIP/ipv4/ip4.o ./Src/LwIP/ipv4/ip4.su ./Src/LwIP/ipv4/ip4_addr.cyclo ./Src/LwIP/ipv4/ip4_addr.d ./Src/LwIP/ipv4/ip4_addr.o ./Src/LwIP/ipv4/ip4_addr.su ./Src/LwIP/ipv4/ip4_frag.cyclo ./Src/LwIP/ipv4/ip4_frag.d ./Src/LwIP/ipv4/ip4_frag.o ./Src/LwIP/ipv4/ip4_frag.su

.PHONY: clean-Src-2f-LwIP-2f-ipv4

