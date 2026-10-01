################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LwIP/altcp.c \
../Src/LwIP/altcp_alloc.c \
../Src/LwIP/altcp_tcp.c \
../Src/LwIP/def.c \
../Src/LwIP/dns.c \
../Src/LwIP/inet_chksum.c \
../Src/LwIP/init.c \
../Src/LwIP/ip.c \
../Src/LwIP/mem.c \
../Src/LwIP/memp.c \
../Src/LwIP/netif.c \
../Src/LwIP/pbuf.c \
../Src/LwIP/raw.c \
../Src/LwIP/stats.c \
../Src/LwIP/sys.c \
../Src/LwIP/tcp.c \
../Src/LwIP/tcp_in.c \
../Src/LwIP/tcp_out.c \
../Src/LwIP/timeouts.c \
../Src/LwIP/udp.c 

OBJS += \
./Src/LwIP/altcp.o \
./Src/LwIP/altcp_alloc.o \
./Src/LwIP/altcp_tcp.o \
./Src/LwIP/def.o \
./Src/LwIP/dns.o \
./Src/LwIP/inet_chksum.o \
./Src/LwIP/init.o \
./Src/LwIP/ip.o \
./Src/LwIP/mem.o \
./Src/LwIP/memp.o \
./Src/LwIP/netif.o \
./Src/LwIP/pbuf.o \
./Src/LwIP/raw.o \
./Src/LwIP/stats.o \
./Src/LwIP/sys.o \
./Src/LwIP/tcp.o \
./Src/LwIP/tcp_in.o \
./Src/LwIP/tcp_out.o \
./Src/LwIP/timeouts.o \
./Src/LwIP/udp.o 

C_DEPS += \
./Src/LwIP/altcp.d \
./Src/LwIP/altcp_alloc.d \
./Src/LwIP/altcp_tcp.d \
./Src/LwIP/def.d \
./Src/LwIP/dns.d \
./Src/LwIP/inet_chksum.d \
./Src/LwIP/init.d \
./Src/LwIP/ip.d \
./Src/LwIP/mem.d \
./Src/LwIP/memp.d \
./Src/LwIP/netif.d \
./Src/LwIP/pbuf.d \
./Src/LwIP/raw.d \
./Src/LwIP/stats.d \
./Src/LwIP/sys.d \
./Src/LwIP/tcp.d \
./Src/LwIP/tcp_in.d \
./Src/LwIP/tcp_out.d \
./Src/LwIP/timeouts.d \
./Src/LwIP/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Src/LwIP/%.o Src/LwIP/%.su Src/LwIP/%.cyclo: ../Src/LwIP/%.c Src/LwIP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -c -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Device/ST/STM32N657xx/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Driver" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc/netif" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc" -O0 -ffunction-sections -fdata-sections -Wall -v -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-LwIP

clean-Src-2f-LwIP:
	-$(RM) ./Src/LwIP/altcp.cyclo ./Src/LwIP/altcp.d ./Src/LwIP/altcp.o ./Src/LwIP/altcp.su ./Src/LwIP/altcp_alloc.cyclo ./Src/LwIP/altcp_alloc.d ./Src/LwIP/altcp_alloc.o ./Src/LwIP/altcp_alloc.su ./Src/LwIP/altcp_tcp.cyclo ./Src/LwIP/altcp_tcp.d ./Src/LwIP/altcp_tcp.o ./Src/LwIP/altcp_tcp.su ./Src/LwIP/def.cyclo ./Src/LwIP/def.d ./Src/LwIP/def.o ./Src/LwIP/def.su ./Src/LwIP/dns.cyclo ./Src/LwIP/dns.d ./Src/LwIP/dns.o ./Src/LwIP/dns.su ./Src/LwIP/inet_chksum.cyclo ./Src/LwIP/inet_chksum.d ./Src/LwIP/inet_chksum.o ./Src/LwIP/inet_chksum.su ./Src/LwIP/init.cyclo ./Src/LwIP/init.d ./Src/LwIP/init.o ./Src/LwIP/init.su ./Src/LwIP/ip.cyclo ./Src/LwIP/ip.d ./Src/LwIP/ip.o ./Src/LwIP/ip.su ./Src/LwIP/mem.cyclo ./Src/LwIP/mem.d ./Src/LwIP/mem.o ./Src/LwIP/mem.su ./Src/LwIP/memp.cyclo ./Src/LwIP/memp.d ./Src/LwIP/memp.o ./Src/LwIP/memp.su ./Src/LwIP/netif.cyclo ./Src/LwIP/netif.d ./Src/LwIP/netif.o ./Src/LwIP/netif.su ./Src/LwIP/pbuf.cyclo ./Src/LwIP/pbuf.d ./Src/LwIP/pbuf.o ./Src/LwIP/pbuf.su ./Src/LwIP/raw.cyclo ./Src/LwIP/raw.d ./Src/LwIP/raw.o ./Src/LwIP/raw.su ./Src/LwIP/stats.cyclo ./Src/LwIP/stats.d ./Src/LwIP/stats.o ./Src/LwIP/stats.su ./Src/LwIP/sys.cyclo ./Src/LwIP/sys.d ./Src/LwIP/sys.o ./Src/LwIP/sys.su ./Src/LwIP/tcp.cyclo ./Src/LwIP/tcp.d ./Src/LwIP/tcp.o ./Src/LwIP/tcp.su ./Src/LwIP/tcp_in.cyclo ./Src/LwIP/tcp_in.d ./Src/LwIP/tcp_in.o ./Src/LwIP/tcp_in.su ./Src/LwIP/tcp_out.cyclo ./Src/LwIP/tcp_out.d ./Src/LwIP/tcp_out.o ./Src/LwIP/tcp_out.su ./Src/LwIP/timeouts.cyclo ./Src/LwIP/timeouts.d ./Src/LwIP/timeouts.o ./Src/LwIP/timeouts.su ./Src/LwIP/udp.cyclo ./Src/LwIP/udp.d ./Src/LwIP/udp.o ./Src/LwIP/udp.su

.PHONY: clean-Src-2f-LwIP

