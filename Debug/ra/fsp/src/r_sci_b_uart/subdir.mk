################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_sci_b_uart/r_sci_b_uart.c 

C_DEPS += \
./ra/fsp/src/r_sci_b_uart/r_sci_b_uart.d 

OBJS += \
./ra/fsp/src/r_sci_b_uart/r_sci_b_uart.o 

SREC += \
dsi_ai_vision.srec 

MAP += \
dsi_ai_vision.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_sci_b_uart/%.o: ../ra/fsp/src/r_sci_b_uart/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -mcpu=cortex-m85+nopacbti -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_gen" -I"." -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/fsp_cfg/bsp" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra_cfg/fsp_cfg" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/src" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/fsp/inc" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/fsp/inc/api" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/fsp/inc/instances" -I"C:/Users/Deived/e2_studio/workspace/dsi_ai_vision/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -Wno-stringop-overflow -Wno-format-truncation -flax-vector-conversions --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

