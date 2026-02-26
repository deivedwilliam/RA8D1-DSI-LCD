################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal_entry.c \
../src/hal_warmstart.c \
../src/i2c_controller.c \
../src/lontium_bridge_lt8912.c \
../src/mipi_dsi_ep.c \
../src/system.c \
../src/uart_ep.c 

C_DEPS += \
./src/hal_entry.d \
./src/hal_warmstart.d \
./src/i2c_controller.d \
./src/lontium_bridge_lt8912.d \
./src/mipi_dsi_ep.d \
./src/system.d \
./src/uart_ep.d 

OBJS += \
./src/hal_entry.o \
./src/hal_warmstart.o \
./src/i2c_controller.o \
./src/lontium_bridge_lt8912.o \
./src/mipi_dsi_ep.o \
./src/system.o \
./src/uart_ep.o 

SREC += \
dsi_ai_vision.srec 

MAP += \
dsi_ai_vision.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -mcpu=cortex-m85+nopacbti -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_gen" -I"." -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/fsp_cfg/bsp" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/fsp_cfg" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/src" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/fsp/inc" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/fsp/inc/api" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/fsp/inc/instances" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/driver" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/fsp_cfg/lvgl/lvgl" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/fsp_cfg/middleware" -std=gnu99 -Wno-stringop-overflow -Wno-format-truncation -flax-vector-conversions --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

