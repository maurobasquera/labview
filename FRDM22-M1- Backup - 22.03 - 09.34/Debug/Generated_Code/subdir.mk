################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/BitIoLdd5.c \
../Generated_Code/Cpu.c \
../Generated_Code/KSDK1.c \
../Generated_Code/LEDpin1.c \
../Generated_Code/LEDpin2.c \
../Generated_Code/LEDpin3.c \
../Generated_Code/MCUC1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/RealTimeLdd1.c \
../Generated_Code/RealTimeLdd2.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/TU3.c \
../Generated_Code/TU4.c \
../Generated_Code/adc.c \
../Generated_Code/blue.c \
../Generated_Code/delay.c \
../Generated_Code/enableModbus.c \
../Generated_Code/green.c \
../Generated_Code/indicationModbus.c \
../Generated_Code/modbusSerial.c \
../Generated_Code/pooling_delay.c \
../Generated_Code/push_button.c \
../Generated_Code/pwm.c \
../Generated_Code/red.c \
../Generated_Code/sleepModbus.c \
../Generated_Code/timeout_delay.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/BitIoLdd5.o \
./Generated_Code/Cpu.o \
./Generated_Code/KSDK1.o \
./Generated_Code/LEDpin1.o \
./Generated_Code/LEDpin2.o \
./Generated_Code/LEDpin3.o \
./Generated_Code/MCUC1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/RealTimeLdd1.o \
./Generated_Code/RealTimeLdd2.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TU3.o \
./Generated_Code/TU4.o \
./Generated_Code/adc.o \
./Generated_Code/blue.o \
./Generated_Code/delay.o \
./Generated_Code/enableModbus.o \
./Generated_Code/green.o \
./Generated_Code/indicationModbus.o \
./Generated_Code/modbusSerial.o \
./Generated_Code/pooling_delay.o \
./Generated_Code/push_button.o \
./Generated_Code/pwm.o \
./Generated_Code/red.o \
./Generated_Code/sleepModbus.o \
./Generated_Code/timeout_delay.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/BitIoLdd5.d \
./Generated_Code/Cpu.d \
./Generated_Code/KSDK1.d \
./Generated_Code/LEDpin1.d \
./Generated_Code/LEDpin2.d \
./Generated_Code/LEDpin3.d \
./Generated_Code/MCUC1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/RealTimeLdd1.d \
./Generated_Code/RealTimeLdd2.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/TU3.d \
./Generated_Code/TU4.d \
./Generated_Code/adc.d \
./Generated_Code/blue.d \
./Generated_Code/delay.d \
./Generated_Code/enableModbus.d \
./Generated_Code/green.d \
./Generated_Code/indicationModbus.d \
./Generated_Code/modbusSerial.d \
./Generated_Code/pooling_delay.d \
./Generated_Code/push_button.d \
./Generated_Code/pwm.d \
./Generated_Code/red.d \
./Generated_Code/sleepModbus.d \
./Generated_Code/timeout_delay.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Static_Code/System" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Static_Code/PDD" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Sources" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


