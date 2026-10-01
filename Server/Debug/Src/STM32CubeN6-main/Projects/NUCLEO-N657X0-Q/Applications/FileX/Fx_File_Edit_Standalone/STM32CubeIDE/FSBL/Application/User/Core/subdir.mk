################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.c 

OBJS += \
./Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.o 

C_DEPS += \
./Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/%.o Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/%.su Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/%.cyclo: ../Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/%.c Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -c -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Device/ST/STM32N657xx/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Driver" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc/netif" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/CMSIS/Include" -I"/home/mfuhrman/Documents/Education/SFSU/2026 Fall/Engr 478 - Lab/Project/Code/ENGR478-Project/Server/Inc" -O0 -ffunction-sections -fdata-sections -Wall -v -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-STM32CubeN6-2d-main-2f-Projects-2f-NUCLEO-2d-N657X0-2d-Q-2f-Applications-2f-FileX-2f-Fx_File_Edit_Standalone-2f-STM32CubeIDE-2f-FSBL-2f-Application-2f-User-2f-Core

clean-Src-2f-STM32CubeN6-2d-main-2f-Projects-2f-NUCLEO-2d-N657X0-2d-Q-2f-Applications-2f-FileX-2f-Fx_File_Edit_Standalone-2f-STM32CubeIDE-2f-FSBL-2f-Application-2f-User-2f-Core:
	-$(RM) ./Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.cyclo ./Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.d ./Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.o ./Src/STM32CubeN6-main/Projects/NUCLEO-N657X0-Q/Applications/FileX/Fx_File_Edit_Standalone/STM32CubeIDE/FSBL/Application/User/Core/syscalls.su

.PHONY: clean-Src-2f-STM32CubeN6-2d-main-2f-Projects-2f-NUCLEO-2d-N657X0-2d-Q-2f-Applications-2f-FileX-2f-Fx_File_Edit_Standalone-2f-STM32CubeIDE-2f-FSBL-2f-Application-2f-User-2f-Core

