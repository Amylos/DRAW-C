################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Container/container.c 

OBJS += \
./App/Container/container.o 

C_DEPS += \
./App/Container/container.d 


# Each subdirectory must supply rules for building sources it contributes
App/Container/%.o: ../App/Container/%.c App/Container/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


