################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EBO.cpp \
../src/VAO.cpp \
../src/VBO.cpp \
../src/collision_detection.cpp \
../src/polygon_maker.cpp \
../src/shaderClass.cpp 

OBJS += \
./src/EBO.o \
./src/VAO.o \
./src/VBO.o \
./src/collision_detection.o \
./src/polygon_maker.o \
./src/shaderClass.o 

CPP_DEPS += \
./src/EBO.d \
./src/VAO.d \
./src/VBO.d \
./src/collision_detection.d \
./src/polygon_maker.d \
./src/shaderClass.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


