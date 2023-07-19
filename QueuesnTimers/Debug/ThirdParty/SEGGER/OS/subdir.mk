################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/OS/%.o ThirdParty/SEGGER/OS/%.su ThirdParty/SEGGER/OS/%.cyclo: ../ThirdParty/SEGGER/OS/%.c ThirdParty/SEGGER/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB15xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I"C:/Users/MSI-NB/Desktop/Work/RTOS_workspace/Common/ThirdParty/FreeRTOS/include" -I"C:/Users/MSI-NB/Desktop/Work/RTOS_workspace/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/MSI-NB/Desktop/Work/RTOS_workspace/Common/ThirdParty/SEGGER/Config" -I"C:/Users/MSI-NB/Desktop/Work/RTOS_workspace/Common/ThirdParty/SEGGER/OS" -I"C:/Users/MSI-NB/Desktop/Work/RTOS_workspace/Common/ThirdParty/SEGGER/SEGGER" -I"C:/Users/MSI-NB/Desktop/Work/RTOS_workspace/Common/ThirdParty/FreeRTOS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-SEGGER-2f-OS

clean-ThirdParty-2f-SEGGER-2f-OS:
	-$(RM) ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.cyclo ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o ./ThirdParty/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.su

.PHONY: clean-ThirdParty-2f-SEGGER-2f-OS

