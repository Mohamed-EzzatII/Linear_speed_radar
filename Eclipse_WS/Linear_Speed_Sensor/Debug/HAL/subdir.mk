################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/buzzer.c \
../HAL/grn_led.c \
../HAL/lcd.c \
../HAL/red_led.c 

OBJS += \
./HAL/buzzer.o \
./HAL/grn_led.o \
./HAL/lcd.o \
./HAL/red_led.o 

C_DEPS += \
./HAL/buzzer.d \
./HAL/grn_led.d \
./HAL/lcd.d \
./HAL/red_led.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


