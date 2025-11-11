################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Pilotes/pilote_Timer14.c 

OBJS += \
./Core/Src/Pilotes/pilote_Timer14.o 

C_DEPS += \
./Core/Src/Pilotes/pilote_Timer14.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Pilotes/%.o Core/Src/Pilotes/%.su Core/Src/Pilotes/%.cyclo: ../Core/Src/Pilotes/%.c Core/Src/Pilotes/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Interfaces" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Pilotes" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Processus" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Services" -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Pilotes

clean-Core-2f-Src-2f-Pilotes:
	-$(RM) ./Core/Src/Pilotes/pilote_Timer14.cyclo ./Core/Src/Pilotes/pilote_Timer14.d ./Core/Src/Pilotes/pilote_Timer14.o ./Core/Src/Pilotes/pilote_Timer14.su

.PHONY: clean-Core-2f-Src-2f-Pilotes

