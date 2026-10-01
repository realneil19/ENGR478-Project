################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LwIP/ipv6/dhcp6.c \
../Src/LwIP/ipv6/ethip6.c \
../Src/LwIP/ipv6/icmp6.c \
../Src/LwIP/ipv6/inet6.c \
../Src/LwIP/ipv6/ip6.c \
../Src/LwIP/ipv6/ip6_addr.c \
../Src/LwIP/ipv6/ip6_frag.c \
../Src/LwIP/ipv6/mld6.c \
../Src/LwIP/ipv6/nd6.c 

OBJS += \
./Src/LwIP/ipv6/dhcp6.o \
./Src/LwIP/ipv6/ethip6.o \
./Src/LwIP/ipv6/icmp6.o \
./Src/LwIP/ipv6/inet6.o \
./Src/LwIP/ipv6/ip6.o \
./Src/LwIP/ipv6/ip6_addr.o \
./Src/LwIP/ipv6/ip6_frag.o \
./Src/LwIP/ipv6/mld6.o \
./Src/LwIP/ipv6/nd6.o 

C_DEPS += \
./Src/LwIP/ipv6/dhcp6.d \
./Src/LwIP/ipv6/ethip6.d \
./Src/LwIP/ipv6/icmp6.d \
./Src/LwIP/ipv6/inet6.d \
./Src/LwIP/ipv6/ip6.d \
./Src/LwIP/ipv6/ip6_addr.d \
./Src/LwIP/ipv6/ip6_frag.d \
./Src/LwIP/ipv6/mld6.d \
./Src/LwIP/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
Src/LwIP/ipv6/%.o Src/LwIP/ipv6/%.su Src/LwIP/ipv6/%.cyclo: ../Src/LwIP/ipv6/%.c Src/LwIP/ipv6/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -c -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Device/ST/STM32N657xx/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Driver" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc/netif" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc" -O0 -ffunction-sections -fdata-sections -Wall -v -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-LwIP-2f-ipv6

clean-Src-2f-LwIP-2f-ipv6:
	-$(RM) ./Src/LwIP/ipv6/dhcp6.cyclo ./Src/LwIP/ipv6/dhcp6.d ./Src/LwIP/ipv6/dhcp6.o ./Src/LwIP/ipv6/dhcp6.su ./Src/LwIP/ipv6/ethip6.cyclo ./Src/LwIP/ipv6/ethip6.d ./Src/LwIP/ipv6/ethip6.o ./Src/LwIP/ipv6/ethip6.su ./Src/LwIP/ipv6/icmp6.cyclo ./Src/LwIP/ipv6/icmp6.d ./Src/LwIP/ipv6/icmp6.o ./Src/LwIP/ipv6/icmp6.su ./Src/LwIP/ipv6/inet6.cyclo ./Src/LwIP/ipv6/inet6.d ./Src/LwIP/ipv6/inet6.o ./Src/LwIP/ipv6/inet6.su ./Src/LwIP/ipv6/ip6.cyclo ./Src/LwIP/ipv6/ip6.d ./Src/LwIP/ipv6/ip6.o ./Src/LwIP/ipv6/ip6.su ./Src/LwIP/ipv6/ip6_addr.cyclo ./Src/LwIP/ipv6/ip6_addr.d ./Src/LwIP/ipv6/ip6_addr.o ./Src/LwIP/ipv6/ip6_addr.su ./Src/LwIP/ipv6/ip6_frag.cyclo ./Src/LwIP/ipv6/ip6_frag.d ./Src/LwIP/ipv6/ip6_frag.o ./Src/LwIP/ipv6/ip6_frag.su ./Src/LwIP/ipv6/mld6.cyclo ./Src/LwIP/ipv6/mld6.d ./Src/LwIP/ipv6/mld6.o ./Src/LwIP/ipv6/mld6.su ./Src/LwIP/ipv6/nd6.cyclo ./Src/LwIP/ipv6/nd6.d ./Src/LwIP/ipv6/nd6.o ./Src/LwIP/ipv6/nd6.su

.PHONY: clean-Src-2f-LwIP-2f-ipv6

