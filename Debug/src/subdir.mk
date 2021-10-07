################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AABB_tree.cpp \
../src/bounding_volume_hierarchy.cpp \
../src/collision_detection.cpp 

OBJS += \
./src/AABB_tree.o \
./src/bounding_volume_hierarchy.o \
./src/collision_detection.o 

CPP_DEPS += \
./src/AABB_tree.d \
./src/bounding_volume_hierarchy.d \
./src/collision_detection.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


