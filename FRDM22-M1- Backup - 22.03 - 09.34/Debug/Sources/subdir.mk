################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/functions.c \
../Sources/main.c \
../Sources/modbusMaster.c 

OBJS += \
./Sources/Events.o \
./Sources/functions.o \
./Sources/main.o \
./Sources/modbusMaster.o 

C_DEPS += \
./Sources/Events.d \
./Sources/functions.d \
./Sources/main.d \
./Sources/modbusMaster.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Static_Code/System" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Static_Code/PDD" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Sources" -I"C:/Users/mauro/Desktop/FRDM22-M1- Backup - 17.03 - 17.36 - Copia - Copia - Copia/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


