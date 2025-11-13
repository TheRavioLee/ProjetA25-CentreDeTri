################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Processus/processusCentreDeTri.c \
../Core/Src/Processus/processusEntreeAnalogique.c \
../Core/Src/Processus/processusEntreesNumeriques.c \
../Core/Src/Processus/processusSortiesNumeriques.c \
../Core/Src/Processus/processus_Affichage.c 

OBJS += \
./Core/Src/Processus/processusCentreDeTri.o \
./Core/Src/Processus/processusEntreeAnalogique.o \
./Core/Src/Processus/processusEntreesNumeriques.o \
./Core/Src/Processus/processusSortiesNumeriques.o \
./Core/Src/Processus/processus_Affichage.o 

C_DEPS += \
./Core/Src/Processus/processusCentreDeTri.d \
./Core/Src/Processus/processusEntreeAnalogique.d \
./Core/Src/Processus/processusEntreesNumeriques.d \
./Core/Src/Processus/processusSortiesNumeriques.d \
./Core/Src/Processus/processus_Affichage.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Processus/%.o Core/Src/Processus/%.su Core/Src/Processus/%.cyclo: ../Core/Src/Processus/%.c Core/Src/Processus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Interfaces" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Pilotes" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Processus" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Services" -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Processus

clean-Core-2f-Src-2f-Processus:
	-$(RM) ./Core/Src/Processus/processusCentreDeTri.cyclo ./Core/Src/Processus/processusCentreDeTri.d ./Core/Src/Processus/processusCentreDeTri.o ./Core/Src/Processus/processusCentreDeTri.su ./Core/Src/Processus/processusEntreeAnalogique.cyclo ./Core/Src/Processus/processusEntreeAnalogique.d ./Core/Src/Processus/processusEntreeAnalogique.o ./Core/Src/Processus/processusEntreeAnalogique.su ./Core/Src/Processus/processusEntreesNumeriques.cyclo ./Core/Src/Processus/processusEntreesNumeriques.d ./Core/Src/Processus/processusEntreesNumeriques.o ./Core/Src/Processus/processusEntreesNumeriques.su ./Core/Src/Processus/processusSortiesNumeriques.cyclo ./Core/Src/Processus/processusSortiesNumeriques.d ./Core/Src/Processus/processusSortiesNumeriques.o ./Core/Src/Processus/processusSortiesNumeriques.su ./Core/Src/Processus/processus_Affichage.cyclo ./Core/Src/Processus/processus_Affichage.d ./Core/Src/Processus/processus_Affichage.o ./Core/Src/Processus/processus_Affichage.su

.PHONY: clean-Core-2f-Src-2f-Processus

