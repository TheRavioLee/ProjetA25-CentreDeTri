################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Pilotes/pilote_BoutonBleu.c \
../Core/Src/Pilotes/pilote_CAN.c \
../Core/Src/Pilotes/pilote_I2C.c \
../Core/Src/Pilotes/pilote_LED_J.c \
../Core/Src/Pilotes/pilote_LED_R.c \
../Core/Src/Pilotes/pilote_LED_V.c \
../Core/Src/Pilotes/pilote_MoteurPH1.c \
../Core/Src/Pilotes/pilote_MoteurPH2.c \
../Core/Src/Pilotes/pilote_MoteurPH3.c \
../Core/Src/Pilotes/pilote_MoteurPH4.c \
../Core/Src/Pilotes/pilote_Timers.c \
../Core/Src/Pilotes/pilote_Triac.c 

OBJS += \
./Core/Src/Pilotes/pilote_BoutonBleu.o \
./Core/Src/Pilotes/pilote_CAN.o \
./Core/Src/Pilotes/pilote_I2C.o \
./Core/Src/Pilotes/pilote_LED_J.o \
./Core/Src/Pilotes/pilote_LED_R.o \
./Core/Src/Pilotes/pilote_LED_V.o \
./Core/Src/Pilotes/pilote_MoteurPH1.o \
./Core/Src/Pilotes/pilote_MoteurPH2.o \
./Core/Src/Pilotes/pilote_MoteurPH3.o \
./Core/Src/Pilotes/pilote_MoteurPH4.o \
./Core/Src/Pilotes/pilote_Timers.o \
./Core/Src/Pilotes/pilote_Triac.o 

C_DEPS += \
./Core/Src/Pilotes/pilote_BoutonBleu.d \
./Core/Src/Pilotes/pilote_CAN.d \
./Core/Src/Pilotes/pilote_I2C.d \
./Core/Src/Pilotes/pilote_LED_J.d \
./Core/Src/Pilotes/pilote_LED_R.d \
./Core/Src/Pilotes/pilote_LED_V.d \
./Core/Src/Pilotes/pilote_MoteurPH1.d \
./Core/Src/Pilotes/pilote_MoteurPH2.d \
./Core/Src/Pilotes/pilote_MoteurPH3.d \
./Core/Src/Pilotes/pilote_MoteurPH4.d \
./Core/Src/Pilotes/pilote_Timers.d \
./Core/Src/Pilotes/pilote_Triac.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Pilotes/%.o Core/Src/Pilotes/%.su Core/Src/Pilotes/%.cyclo: ../Core/Src/Pilotes/%.c Core/Src/Pilotes/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Interfaces" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Pilotes" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Processus" -I"/Users/thomaslajoie/STM32CubeIDE/workspace_1.18.0/ProjetA25_CentreDeTri/Core/Inc/Services" -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Pilotes

clean-Core-2f-Src-2f-Pilotes:
	-$(RM) ./Core/Src/Pilotes/pilote_BoutonBleu.cyclo ./Core/Src/Pilotes/pilote_BoutonBleu.d ./Core/Src/Pilotes/pilote_BoutonBleu.o ./Core/Src/Pilotes/pilote_BoutonBleu.su ./Core/Src/Pilotes/pilote_CAN.cyclo ./Core/Src/Pilotes/pilote_CAN.d ./Core/Src/Pilotes/pilote_CAN.o ./Core/Src/Pilotes/pilote_CAN.su ./Core/Src/Pilotes/pilote_I2C.cyclo ./Core/Src/Pilotes/pilote_I2C.d ./Core/Src/Pilotes/pilote_I2C.o ./Core/Src/Pilotes/pilote_I2C.su ./Core/Src/Pilotes/pilote_LED_J.cyclo ./Core/Src/Pilotes/pilote_LED_J.d ./Core/Src/Pilotes/pilote_LED_J.o ./Core/Src/Pilotes/pilote_LED_J.su ./Core/Src/Pilotes/pilote_LED_R.cyclo ./Core/Src/Pilotes/pilote_LED_R.d ./Core/Src/Pilotes/pilote_LED_R.o ./Core/Src/Pilotes/pilote_LED_R.su ./Core/Src/Pilotes/pilote_LED_V.cyclo ./Core/Src/Pilotes/pilote_LED_V.d ./Core/Src/Pilotes/pilote_LED_V.o ./Core/Src/Pilotes/pilote_LED_V.su ./Core/Src/Pilotes/pilote_MoteurPH1.cyclo ./Core/Src/Pilotes/pilote_MoteurPH1.d ./Core/Src/Pilotes/pilote_MoteurPH1.o ./Core/Src/Pilotes/pilote_MoteurPH1.su ./Core/Src/Pilotes/pilote_MoteurPH2.cyclo ./Core/Src/Pilotes/pilote_MoteurPH2.d ./Core/Src/Pilotes/pilote_MoteurPH2.o ./Core/Src/Pilotes/pilote_MoteurPH2.su ./Core/Src/Pilotes/pilote_MoteurPH3.cyclo ./Core/Src/Pilotes/pilote_MoteurPH3.d ./Core/Src/Pilotes/pilote_MoteurPH3.o ./Core/Src/Pilotes/pilote_MoteurPH3.su ./Core/Src/Pilotes/pilote_MoteurPH4.cyclo ./Core/Src/Pilotes/pilote_MoteurPH4.d ./Core/Src/Pilotes/pilote_MoteurPH4.o ./Core/Src/Pilotes/pilote_MoteurPH4.su ./Core/Src/Pilotes/pilote_Timers.cyclo ./Core/Src/Pilotes/pilote_Timers.d ./Core/Src/Pilotes/pilote_Timers.o ./Core/Src/Pilotes/pilote_Timers.su ./Core/Src/Pilotes/pilote_Triac.cyclo ./Core/Src/Pilotes/pilote_Triac.d ./Core/Src/Pilotes/pilote_Triac.o ./Core/Src/Pilotes/pilote_Triac.su

.PHONY: clean-Core-2f-Src-2f-Pilotes

