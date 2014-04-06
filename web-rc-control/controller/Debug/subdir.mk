################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gpio_control.c \
../libjson.c \
../liblogin.c \
../libserial.c \
../utils.c \
../webcontrol.c 

OBJS += \
./gpio_control.o \
./libjson.o \
./liblogin.o \
./libserial.o \
./utils.o \
./webcontrol.o 

C_DEPS += \
./gpio_control.d \
./libjson.d \
./liblogin.d \
./libserial.d \
./utils.d \
./webcontrol.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


