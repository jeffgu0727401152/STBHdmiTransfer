################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/demo.c \
../src/hwdata-b5-R.c \
../src/hwdata-gb-R.c \
../src/hwdataT.c 

OBJS += \
./src/demo.o \
./src/hwdata-b5-R.o \
./src/hwdata-gb-R.o \
./src/hwdataT.o 

C_DEPS += \
./src/demo.d \
./src/hwdata-b5-R.d \
./src/hwdata-gb-R.d \
./src/hwdataT.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


